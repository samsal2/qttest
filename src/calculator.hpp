#pragma once

#include <QLineEdit>
#include <QToolButton>
#include <QWidget>
#include <vector>

namespace qttest {

class button : public QToolButton {
private:
  Q_OBJECT

public:
  explicit button(QString const &text, QWidget *parent = nullptr);
  virtual ~button();

  auto sizeHint() const -> QSize override;
};

class calculator : public QWidget {
private:
  enum class click_op {
    digit,
    unary,
    add,
    mul,
    eq,
    point,
    change_sign,
    backspace,
  };

  Q_OBJECT

public:
  explicit calculator(QWidget *parent = nullptr);
  virtual ~calculator();

private slots:
  auto on_click() -> void;
  auto create_button(QString const &text, char const *member) -> button * {
    auto *btn = new button(text);
    connect(btn, SIGNAL(clicked()), this, member);
    return btn;
  }

private:
  QLineEdit *display;
  std::array<button *, 10> buttons = {};
};

} // namespace qttest
