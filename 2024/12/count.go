package main

import (
	"database/sql"
	"fmt"
	"log"
	"net"
	"net/http"
	"sync"
	"time"

	_ "github.com/marcboeker/go-duckdb"
)

var (
	db              *sql.DB
	activeSessions2 = make(map[string]string) // sessionID -> username
	sessionCounter2 = 0
	mutex           sync.Mutex
)

// 初始化数据库
func initDB() {
	var err error
	db, err = sql.Open("duckdb", "duckdb.db")
	if err != nil {
		log.Fatal("数据库连接失败:", err)
	}

	_, err = db.Exec(`
		CREATE TABLE IF NOT EXISTS accounts (
			username TEXT PRIMARY KEY,
			password TEXT NOT NULL,
			visit_count INTEGER DEFAULT 0,
			last_login TIMESTAMP
		)
	`)
	if err != nil {
		log.Fatal("创建表失败:", err)
	}
}

// 创建新会话 ID
func createSessionID2() string {
	mutex.Lock()
	defer mutex.Unlock()
	sessionCounter2++
	return fmt.Sprintf("session-%d", sessionCounter2)
}

// 获取客户端 IP 地址
func getIP(r *http.Request) string {
	ip, _, _ := net.SplitHostPort(r.RemoteAddr)
	return ip
}

// 注册用户
func registerHandler(w http.ResponseWriter, r *http.Request) {
	if r.Method == http.MethodPost {
		username := r.FormValue("username")
		password := r.FormValue("password")

		_, err := db.Exec("INSERT INTO accounts (username, password) VALUES (?, ?)", username, password)
		if err != nil {
			http.Error(w, "注册失败: 用户名可能已存在", http.StatusConflict)
			return
		}
		http.Redirect(w, r, "/login", http.StatusFound)
		return
	}

	fmt.Fprint(w, `
		<!DOCTYPE html>
		<html lang="zh">
		<head>
			<meta charset="UTF-8">
			<title>注册</title>
		</head>
		<body>
			<h1>注册</h1>
			<form action="/register" method="POST">
				<label for="username">用户名:</label>
				<input type="text" id="username" name="username" required><br>
				<label for="password">密码:</label>
				<input type="password" id="password" name="password" required><br>
				<button type="submit">注册</button>
			</form>
		</body>
		</html>
	`)
}

// 登录用户
func loginHandler2(w http.ResponseWriter, r *http.Request) {
	if r.Method == http.MethodPost {
		username := r.FormValue("username")
		password := r.FormValue("password")

		var dbPassword string
		err := db.QueryRow("SELECT password FROM accounts WHERE username = ?", username).Scan(&dbPassword)
		if err != nil || dbPassword != password {
			http.Error(w, "用户名或密码错误", http.StatusUnauthorized)
			return
		}

		_, err = db.Exec("UPDATE accounts SET visit_count = visit_count + 1, last_login = ? WHERE username = ?", time.Now(), username)
		if err != nil {
			http.Error(w, "登录时更新数据失败", http.StatusInternalServerError)
			return
		}

		sessionID := createSessionID2()
		mutex.Lock()
		activeSessions2[sessionID] = username
		mutex.Unlock()

		http.Redirect(w, r, "/stats?session="+sessionID, http.StatusFound)
		return
	}

	fmt.Fprint(w, `
		<!DOCTYPE html>
		<html lang="zh">
		<head>
			<meta charset="UTF-8">
			<title>登录</title>
		</head>
		<body>
			<h1>登录</h1>
			<form action="/login" method="POST">
				<label for="username">用户名:</label>
				<input type="text" id="username" name="username" required><br>
				<label for="password">密码:</label>
				<input type="password" id="password" name="password" required><br>
				<button type="submit">登录</button>
			</form>
		</body>
		</html>
	`)
}

// 在线人数统计
func statsHandler(w http.ResponseWriter, r *http.Request) {
	sessionID := r.URL.Query().Get("session")
	if sessionID == "" {
		http.Error(w, "无效的会话，请重新登录", http.StatusUnauthorized)
		return
	}

	mutex.Lock()
	_, loggedIn := activeSessions2[sessionID]
	if !loggedIn {
		mutex.Unlock()
		http.Error(w, "会话无效，请重新登录", http.StatusUnauthorized)
		return
	}
	mutex.Unlock()

	rows, err := db.Query("SELECT username, visit_count, last_login FROM accounts")
	if err != nil {
		http.Error(w, "无法查询用户数据", http.StatusInternalServerError)
		return
	}
	defer rows.Close()

	fmt.Fprintf(w, `
		<!DOCTYPE html>
		<html lang="zh">
		<head>
			<meta charset="UTF-8">
			<title>在线人数统计</title>
		</head>
		<body>
			<h1>在线人数统计</h1>
			<p>当前在线人数: %d</p>
			<ul>
	`, len(activeSessions2))

	for rows.Next() {
		var uname string
		var visitCount int
		var lastLogin time.Time
		if err := rows.Scan(&uname, &visitCount, &lastLogin); err != nil {
			continue
		}
		_, err := fmt.Fprintf(w, "<li>用户名: %s, 访问次数: %d, 上次登录: %s</li>", uname, visitCount, lastLogin.Format("2006-01-02 15:04:05"))
		if err != nil {
			return
		}
	}

	_, err = fmt.Fprint(w, `
			</ul>
			<a href="/login">返回登录</a>
		</body>
		</html>
	`)
	if err != nil {
		return
	}
}

func main() {
	initDB()
	defer func(db *sql.DB) {
		err := db.Close()
		if err != nil {
			println(err.Error())
		}
	}(db)

	http.HandleFunc("/register", registerHandler)
	http.HandleFunc("/login", loginHandler2)
	http.HandleFunc("/stats", statsHandler)

	fmt.Println("服务启动，访问 http://localhost:8080")
	if err := http.ListenAndServe(":8080", nil); err != nil {
		fmt.Println("服务启动失败:", err)
	}
}
