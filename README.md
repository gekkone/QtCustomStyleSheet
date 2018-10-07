# QtCustomStyleSheet
Доработка стиля QSS фреймворка Qt
Основная идея проекта доработать стили QSS для возможности их совместного использования с обычными стилями и исправление багов отрисовки
На данный момент стабильно работает на версии Qt 4.8

## Реализованный функционал
* Может использоваться совместо с другими стилями (QStyle)
* Исправлен баг с отрисовкой границ скроллируемых виджетов на версии Qt 4.8
## Планы на следующий релиз
* Исправление багов отрисовки для правил стилей использующих в селекторах динамические свойства, например
```css
QWidget[myProperty="someValue"] {
/* правила */
}
```
* Реализация обновления правил отрисовки при обновлении значений динамических свойств
