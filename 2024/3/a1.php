<?php
function calculate_carbon_emission($distance, $transportation_mode) {
    /*
    根据出行距离和出行方式计算碳排放量
    :param float $distance: 出行距离（公里）
    :param string $transportation_mode: 出行方式
    :return float: 碳排放量（千克）
    */
    $carbon_emission_factors = [
        '步行' => 0,        // 步行假设为0碳排放
        '自行车' => 0,      // 自行车假设为0碳排放
        '电动车' => 0.00011,// 电动车每公里碳排放因子
        '公交车' => 0.011,  // 公交车每公里碳排放因子
        '小汽车' => 0.184,  // 小汽车每公里碳排放因子
        '火车' => 0.04,     // 火车每公里碳排放因子
        '飞机' => 0.257,    // 飞机每公里碳排放因子
    ];

    // 获取对应的碳排放因子
    $factor = $carbon_emission_factors[$transportation_mode] ?? 0;

    // 计算碳排放量
    $carbon_emission = $distance * $factor;
    return $carbon_emission;
}

// 用户输入出行距离和出行方式
$distance = (float) readline("请输入您的出行距离（公里）: ");
$transportation_mode = readline("请输入您的出行方式（步行/自行车/电动车/公交车/小汽车/火车/飞机）: ");

// 计算并输出结果
$carbon_emission1 = calculate_carbon_emission($distance, $transportation_mode);
printf("您本次出行的碳排放量大约为：%.2f 千克\n", $carbon_emission1);

function calculate_electric_carbon_emission($time, $volume) {
    /*
    根据用电时间和用电度数计算碳排放量
    :param float $time: 用电时间（小时）
    :param float $volume: 用电度数
    :return float: 碳排放量（千克）
    */
    // 计算碳排放量
    $carbon_emission = $time * 0.6671;
    return $carbon_emission;
}

// 用户输入用电时间和用电度数
$time = (float) readline("请输入您的用电时间（小时）: ");
$volume = (float) readline("请输入您的用电度数: ");

// 计算并输出结果
$carbon_emission2 = calculate_electric_carbon_emission($time, $volume);
printf("您本次用电的碳排放量大约为：%.2f 千克\n", $carbon_emission2);

// 计算总碳排放量
$total_carbon_emission = $carbon_emission1 + $carbon_emission2;
printf("总碳排放量为：%.2f 千克\n", $total_carbon_emission);
?>
