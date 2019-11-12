package mahjong

import (
	"github.com/googollee/go-socket.io"
	"github.com/satori/go.uuid"
)

// Player's state
const (
	WAITING = 0
	MATCHED = 1
	READY   = 2
	PLAYING = 4
	LEAVE   = 8
)

// NewIPlayer creates a new player info
func NewIPlayer(name string, uuid string) *IPlayer {
	return &IPlayer{ name, uuid, "", nil, WAITING, -1, len(name) > 3 && name[0:3] == "bot", 2 }
}

// IPlayer represents the player's info
type IPlayer struct {
	Name       string
	UUID       string
	Room       string
	Socket     *socketio.Socket
	State      int
	Index      int
	IsBot      bool
	LeaveCount int
}

// PlayerManager represents the array of pointer of IPlayer
type PlayerManager []*IPlayer

// PlayerList is a PlayerManager
var PlayerList PlayerManager

// GetNameList returns the list of player's name
func GetNameList(list []*IPlayer) []string {
	var nameList []string
	for _, player := range list {
		nameList = append(nameList, player.Name)
	}
	return nameList
}

// GetUUIDList returns the list of player's uuid
func GetUUIDList(list []IPlayer) []string {
	var uuidList []string
	for _, player := range list {
		uuidList = append(uuidList, player.UUID)
	}
	return uuidList
}

// AddPlayer adds a new player into PlayerManager
func AddPlayer(name string) (string, bool) {
	if FindPlayerByName(name) != -1 {
		return "", true
	}
	var _uuid string
	for {
		_uuid = uuid.Must(uuid.NewV4()).String()
		if FindPlayerByUUID(_uuid) == -1 {
			break
		}
	}
	PlayerList = append(PlayerList, NewIPlayer(name, _uuid))
	return _uuid, false
}

// RemovePlayer remove a player from PlayerList
func RemovePlayer(id int) {
	if id >= 0 && id < len(PlayerList) {
		PlayerList = append((PlayerList)[: id], (PlayerList)[id + 1: ]...)
	}
}

// FindPlayerByName gets player's index by player's name
func FindPlayerByName(name string) int {
	for index, player := range PlayerList {
		if player.Name == name {
			return index
		}
	}
	return -1
}

// FindPlayerByUUID gets player's index by player's uuid
func FindPlayerByUUID(uuid string) int {
	for index, player := range PlayerList {
		if player.UUID == uuid {
			return index
		}
	}
	return -1
}

// FindPlayerBySocket gets player's index by player's socket
func FindPlayerBySocket(socket socketio.Socket) int {
	for index, player := range PlayerList {
		if (*player.Socket).Id() == socket.Id() {
			return index
		}
	}
	return -1
}

// FindPlayerListInRoom gets list of player which in the same room
func FindPlayerListInRoom(room string, checkIsBot int) []*IPlayer {
	var list []*IPlayer
	for _, player := range PlayerList {
		if player.Room == room && (checkIsBot == -1 || checkIsBot == 0 && !player.IsBot || checkIsBot == 1 && player.IsBot) {
			list = append(list, player)
			if len(list) == 4 {
				break
			}
		}
	}
	return list
}

// FindPlayerListIsSameState gets list of player which are same state
func FindPlayerListIsSameState(state int, checkIsBot int) []*IPlayer {
	var list []*IPlayer
	for _, player := range PlayerList {
		if player.State == state && (checkIsBot == -1 || checkIsBot == 0 && !player.IsBot || checkIsBot == 1 && player.IsBot) {
			list = append(list, player)
		}
	}
	return list
}

// Auth authenticates a player
func Auth(room string, uuid string) bool {
	for _, player := range PlayerList {
		if player.Room == room && player.UUID == uuid {
			if player.State != MATCHED {
				player.LeaveCount++
			}
			return true
		}
	}
	return false
}

//Disconnect handles the player's socket disconnect
func Disconnect(socket socketio.Socket) int {
	index := FindPlayerBySocket(socket)
	if index != -1 {
		PlayerList[index].LeaveCount--
	}
	return index
}