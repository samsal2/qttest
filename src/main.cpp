#include <QApplication>
#include "calculator.hpp"
#include <memory>
#include <cassert>


int main(int argc, char **argv) {
  auto app = QApplication(argc, argv);
  auto widget = std::make_unique<qttest::calculator>();
  widget->setWindowTitle("qttest");
  widget->resize(800, 600);
  widget->show();
  return QApplication::exec();
}
