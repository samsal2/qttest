#include "calculator.hpp"

#include <QGridLayout>
#include <algorithm>

namespace qttest {

calculator::calculator(QWidget *parent) : QWidget(parent) {
  display = new QLineEdit("0");
  display->setReadOnly(true);
  display->setAlignment(Qt::AlignRight);
  display->setMaxLength(10);

  using std::begin;
  using std::end;
  auto current = 0;
  std::generate(begin(buttons), end(buttons), [this, &current] {
    return create_button(QString::number(current), SLOT(on_click()));
  });

#if 0
  auto *point = create_button(tr("."), SLOT(on_click()));
  auto *change_sign = create_button("+/-", SLOT(on_click()));
  auto *backspace = create_button("Backspace", SLOT(on_click()));
#endif

  auto *layout = new QGridLayout();
  layout->setSizeConstraint(QLayout::SetFixedSize);
  current = 0;
  std::for_each(begin(buttons), end(buttons),
                [layout, &current](auto *button) {
                  auto row = ((9 - current) / 3) + 2;
                  auto column = ((current - 1) % 3) + 1;
                  layout->addWidget(button, row, column);
                });

  setLayout(layout);
  setWindowTitle("Calculator");
}

calculator::~calculator() = default;

auto calculator::on_click() -> void {
  [[maybe_unused]] auto *b = qobject_cast<button *>(sender());
}

button::button(QString const &text, QWidget *parent) : QToolButton(parent) {
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  setText(text);
}

button::~button() = default;

auto button::sizeHint() const -> QSize {
  auto size = QToolButton::sizeHint();
  size.rheight() += 20;
  size.rwidth() = std::max(size.width(), size.height());
  return size;
}
} // namespace qttest
