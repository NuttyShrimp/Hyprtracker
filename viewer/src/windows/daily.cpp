#include "daily.hpp"
#include "../charts/barChart.hpp"
#include <iostream>

Daily::Daily() {
  BarChart chart = BarChart(
      {{"S", 1}, {"M", 2}, {"T", 3}, {"T", 2}, {"F", 1}, {"S", 2}, {"S", 3}});
  set_center_widget(chart);
}
Daily::~Daily() {}
