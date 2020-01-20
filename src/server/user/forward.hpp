#ifndef _USER_FORWARD_H
#define _USER_FORWARD_H

#include <memory>

class PalaceConnection;
class Session;

using PalaceConnectionPtr = std::shared_ptr<PalaceConnection>;
using SessionPtr = std::shared_ptr<Session>;
using SessionRef = std::weak_ptr<Session>;

#endif // _USER_FORWARD_H
