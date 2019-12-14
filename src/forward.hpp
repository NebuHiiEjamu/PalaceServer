#ifndef _PALACE_FORWARD_H
#define _PALACE_FORWARD_H

#include <memory>

class Asset;
class Draw;
class Image;
class LooseProp;
class Room;
class PalaceServer;
class Spot;
class State;

using AssetPtr = std::shared_ptr<Asset>;
using AssetRef = std::weak_ptr<Asset>;
using DrawPtr = std::shared_ptr<Draw>;
using DrawRef = std::weak_ptr<Draw>;
using ImagePtr = std::shared_ptr<Image>;
using ImageRef = std::weak_ptr<Image>;
using LoosePropPtr = std::shared_ptr<LooseProp>;
using LoosePropRef = std::weak_ptr<LooseProp>;
using PalaceServerRef = std::weak_ptr<PalaceServer>;
using RoomPtr = std::shared_ptr<Room>;
using RoomRef = std::weak_ptr<Room>;
using SpotPtr = std::shared_ptr<Spot>;
using SpotRef = std::weak_ptr<Spot>;

#endif // _PALACE_FORWARD_H
