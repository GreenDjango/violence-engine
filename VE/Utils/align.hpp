/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** Align
*/

#ifndef ALIGN_HPP_
#define ALIGN_HPP_

namespace ve {

enum AlignFlag {
    FlagLeft = 0x0001,
    FlagRight = 0x0002,
    FlagHCenter = 0x0004,
    FlagHorizontal_Mask = FlagLeft | FlagRight | FlagHCenter,

    FlagTop = 0x0008,
    FlagBottom = 0x0010,
    FlagVCenter = 0x0020,
    FlagVertical_Mask = FlagTop | FlagBottom | FlagVCenter,
};

enum Align {
    LeftTop = FlagLeft | FlagTop,
    RightTop = FlagRight | FlagTop,
    CenterTop = FlagHCenter | FlagTop,

    LeftBottom = FlagLeft | FlagBottom,
    RightBottom = FlagRight | FlagBottom,
    CenterBottom = FlagHCenter | FlagBottom,

    LeftCenter = FlagLeft | FlagVCenter,
    RightCenter = FlagRight | FlagVCenter,
    CenterCenter = FlagHCenter | FlagVCenter
};

} // namespace ve

#endif /* !ALIGN_HPP_ */
