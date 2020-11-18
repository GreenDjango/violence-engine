/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** DebugDraw
*/

#ifndef DEBUGDRAW_HPP_
#define DEBUGDRAW_HPP_

#include "VE/Core/classes/Clock.hpp"
#include "VE/Utils/align.hpp"

namespace ve {

class DebugDraw {
    friend class DebugSystem;

public:

    DebugDraw() : align(Align::RightTop),
                  _fpsLast(0),
                  _fpsCount(0),
                  _drawAverage(0),
                  _drawAverageLast(0),
                  _drawCount(0),
                  _physicAverage(0),
                  _physicAverageLast(0),
                  _physicCount(0),
                  _sleepAverage(0),
                  _sleepAverageLast(0),
                  _sleepCount(0) {}

    Align align;

    float getFps() const { return _fpsLast; }
    float getDrawAverage() const { return _drawAverageLast; }
    float getPhysicAverage() const { return _physicAverageLast; }
    float getSleepAverage() const { return _sleepAverageLast; }

    void beginDraw() {
        _drawClock.restart();
    }
    void endDraw() {
        _drawCount++;
        _drawAverage = _drawAverage + (_drawClock.getElapsedSec() - _drawAverage) / _drawCount;
    }

    void beginPhysic() {
        _physicClock.restart();
    }
    void endPhysic() {
        _physicCount++;
        _physicAverage = _physicAverage + (_physicClock.getElapsedSec() - _physicAverage) / _physicCount;
    }

    void beginSleep() {
        _sleepClock.restart();
    }
    void endSleep() {
        _sleepCount++;
        _sleepAverage = _sleepAverage + (_sleepClock.getElapsedSec() - _sleepAverage) / _sleepCount;
    }

protected:
    void updateFps() {
        _fpsCount++;
        if (_fpsClock.getElapsedMs() >= 1000) {
            float elapsed = _fpsClock.getElapsedSec();
            _fpsClock.restart();
            _fpsLast = ((float)_fpsCount) / elapsed;
            _fpsCount = 0;

            _drawAverageLast = _drawAverage;
            _drawAverage = 0;
            _drawCount = 0;

            _physicAverageLast = _physicAverage;
            _physicAverage = 0;
            _physicCount = 0;

            _sleepAverageLast = _sleepAverage;
            _sleepAverage = 0;
            _sleepCount = 0;
        }
    }

private:
    Clock _fpsClock;
    float _fpsLast;
    int _fpsCount;
    Clock _drawClock;
    float _drawAverage;
    float _drawAverageLast;
    int _drawCount;
    Clock _physicClock;
    float _physicAverage;
    float _physicAverageLast;
    int _physicCount;
    Clock _sleepClock;
    float _sleepAverage;
    float _sleepAverageLast;
    int _sleepCount;
};

} // namespace ve

#endif /* !DEBUGDRAW_HPP_ */
