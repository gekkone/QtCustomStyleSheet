//#ifndef STYLEANIMATION_H
//#define STYLEANIMATION_H

////#include <QtWidgets/private/qtwidgetsglobal_p.h>
//#include "qabstractanimation.h"
//#include "qdatetime.h"
//#include "qimage.h"

//class QStyleAnimation : public QAbstractAnimation
//{
//    Q_OBJECT

//public:
//    QStyleAnimation(QObject *target);
//    virtual ~QStyleAnimation();

//    QObject *target() const;

//    int duration() const;
//    void setDuration(int duration);

//    int delay() const;
//    void setDelay(int delay);

//    QTime startTime() const;
//    void setStartTime(const QTime &time);

//    enum FrameRate {
//        DefaultFps,
//        SixtyFps,
//        ThirtyFps,
//        TwentyFps,
//        FifteenFps
//    };

//    FrameRate frameRate() const;
//    void setFrameRate(FrameRate fps);

//    void updateTarget();

//public Q_SLOTS:
//    void start();

//protected:
//    virtual bool isUpdateNeeded() const;
//    virtual void updateCurrentTime(int time);

//private:
//    int _delay;
//    int _duration;
//    QTime _startTime;
//    FrameRate _fps;
//    int _skip;
//};

//class QProgressStyleAnimation : public QStyleAnimation
//{
//    Q_OBJECT

//public:
//    QProgressStyleAnimation(int speed, QObject *target);

//    int animationStep() const;
//    int progressStep(int width) const;

//    int speed() const;
//    void setSpeed(int speed);

//protected:
//    bool isUpdateNeeded() const;

//private:
//    int _speed;
//    mutable int _step;
//};

//class QNumberStyleAnimation : public QStyleAnimation
//{
//    Q_OBJECT

//public:
//    QNumberStyleAnimation(QObject *target);

//    qreal startValue() const;
//    void setStartValue(qreal value);

//    qreal endValue() const;
//    void setEndValue(qreal value);

//    qreal currentValue() const;

//protected:
//    bool isUpdateNeeded() const;

//private:
//    qreal _start;
//    qreal _end;
//    mutable qreal _prev;
//};

//class QBlendStyleAnimation : public QStyleAnimation
//{
//    Q_OBJECT

//public:
//    enum Type { Transition, Pulse };

//    QBlendStyleAnimation(Type type, QObject *target);

//    QImage startImage() const;
//    void setStartImage(const QImage& image);

//    QImage endImage() const;
//    void setEndImage(const QImage& image);

//    QImage currentImage() const;

//protected:
//    virtual void updateCurrentTime(int time);

//private:
//    Type _type;
//    QImage _start;
//    QImage _end;
//    QImage _current;
//};

//class QScrollbarStyleAnimation : public QNumberStyleAnimation
//{
//    Q_OBJECT

//public:
//    enum Mode { Activating, Deactivating };

//    QScrollbarStyleAnimation(Mode mode, QObject *target);

//    Mode mode() const;

//    bool wasActive() const;
//    void setActive(bool active);

//private slots:
//    void updateCurrentTime(int time);

//private:
//    Mode _mode;
//    bool _active;
//};

//#endif // STYLEANIMATION_H
