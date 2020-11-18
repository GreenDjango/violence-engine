/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** Animation
*/

#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

namespace ve {

struct Animation {
    unsigned int frameWidth;
    unsigned int frameHeight;
    unsigned int xSize;
    unsigned int ySize;
    unsigned int msByFrame;
    bool loop;
    bool foreward;
    unsigned int frameIndex;
    unsigned int msElapsed;
    bool firstRender;

    Animation() {}

    Animation(unsigned int frameWidth, unsigned int frameHeight, unsigned int xSize, unsigned int ySize, unsigned int msByFrame = 1000, bool loop = true, bool foreward = true, unsigned int frameIndex = 0)
        : frameWidth(frameWidth), frameHeight(frameHeight), xSize(xSize), ySize(ySize), msByFrame(msByFrame), loop(loop), foreward(foreward), frameIndex(frameIndex), msElapsed(0), firstRender(true) {}

    static Animation create(unsigned int imgWidth, unsigned int imgHeight, unsigned int xSize, unsigned int ySize, unsigned int msByFrame = 1000, bool loop = true, bool foreward = true, unsigned int frameIndex = 0) {
        return Animation{ imgWidth / xSize, imgHeight / ySize, xSize, ySize, msByFrame, loop, foreward, frameIndex };
    }
};

} // namespace ve

#endif /* !ANIMATION_HPP_ */