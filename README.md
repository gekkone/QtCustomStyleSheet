# QtCustomStyleSheet
Доработка стиля QSS фреймворка Qt
Основная идея проекта доработать стили QSS для возможности их совместного использования с обычными стилями и исправление багов отрисовки
На данный момент стабильно работает на версии Qt 4.8

## Реализованный функционал
* Может использоваться совместо с другими стилями (QStyle)
* Исправлен баг с отрисовкой границ скроллируемых виджетов на версии Qt 4.8
* Реализация обновления правил отрисовки при обновлении значений динамических свойств (такие свойства должны быть добавлены при помощи метода addStyleProperty())
## Планы на следующий релиз
* Реализация кеширования стилей для значений динамических свойств. На данный момент стили для виджетов, имеющих одно из установленных через addStyleProperty() свойств, не кешируются благодаря чему стили обновляются при изменении свойства, но это уменьшает скорость отрисовки.
* Рефакторинг кода
