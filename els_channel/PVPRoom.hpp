#pragma once

#include "Player.hpp"
#include "PacketBuilder.hpp"
#include <set>

namespace els {

	class PVPRoom {

	private:
		int m_id;
		int m_maxplayer;
		int m_kill; // 擊殺數
		int m_mapid; // 地圖ID WORLD_ID
		int m_type; // 團隊戰 = 1 生存戰 = 2
		std::wstring m_roomname;
		std::wstring m_password;
		bool m_open; // false = 不公開房間 true = 公開房間
		bool m_prop; // 道具戰
		float m_second; // 秒數
		Player m_leader;
//		std::map<int, Player*> m_players;

	public:
		PVPRoom(int id);
		PVPRoom() { }
		~PVPRoom() { }

		std::map<int, Player*> m_players;

		int getID();

		int getMaxPlayer();
		int getPlayerSize();
		int getType();
		int getKill();
		int getMapId();
		std::wstring getRoomName();
		std::wstring getPassword();
		bool getOpen();
		bool getProp();
		float getSecond();
		Player getLeader();

		std::map<int, Player*>* getPlayers();
		void addPlayer(Player* player);
		void removePlayer(int id);

		void setMaxPlayer(int value);
		void setType(int value);
		void setKill(int value);
		void setMapId(int value);
		void setRoomName(std::wstring name);
		void setPassword(std::wstring password);
		void setOpen(bool b);
		void setProp(bool b);
		void setSecond(float s);
		void setLeader(Player p);

		void writeRoomInfoData(PacketBuilder& pb);
		void writeRoomPlayersData(PacketBuilder& pb);
		void writeEmptyPlayerData(PacketBuilder& pb, int index, int state);
	};


}