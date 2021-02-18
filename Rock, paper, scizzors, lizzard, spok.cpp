#include "pch.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/*
программа рассчитывает турнир камень, ножницы, бумага, ящерица, спок
на ввод подаются число игроков N и затем список номер игрока и тип, который он будет выбрасывать весь турнир
при ситуации, когда игроки выбрасывают одинаково побеждает игрок с меньшим номером
на выходе пишется номер победившего игрока и список его противников
*/

enum typePlayed
{
	ROCK,
	PAPER,
	SCISSORS,
	SPOCK,
	LIZARD,
	NUMBER_OF_TYPES
};

class Player
{
private:
	int m_num;
	typePlayed m_play;
	vector<int> m_opponents;
	bool m_inGame;

public:
	Player(int num, char play) : m_num(num), m_inGame(true)
	{
		if (play == 'R')
			m_play = ROCK;
		if (play == 'P')
			m_play = PAPER;
		if (play == 'C')
			m_play = SCISSORS;
		if (play == 'S')
			m_play = SPOCK;
		if (play == 'L')
			m_play = LIZARD;
	}

	bool isInGame() const { return m_inGame; }
	int getNum() const { return m_num; }
	int getPlay() const { return m_play; }
	void isDefeated() { m_inGame = false; }
	void Defeated(int num) { m_opponents.push_back(num); }
	void printOpponents()
	{
		for (int num : m_opponents)
			cout << num << " ";
		cout << endl;
	}

	void playMatch(Player &opponent)
	{
		if (m_play == ROCK)
		{
			switch (opponent.getPlay())
			{
			case SCISSORS:
			case LIZARD:
				m_opponents.push_back(opponent.getNum());
				opponent.isDefeated();
				break;
			case PAPER:
			case SPOCK:
				opponent.Defeated(m_num);
				m_inGame = false;
				break;
			case ROCK:
				if (m_num < opponent.getNum())
				{
					m_opponents.push_back(opponent.getNum());
					opponent.isDefeated();
				}
				else
				{
					opponent.Defeated(m_num);
					m_inGame = false;
				}
				break;
			}
		}
		if (m_play == SCISSORS)
		{
			switch (opponent.getPlay())
			{
			case PAPER:
			case LIZARD:
				m_opponents.push_back(opponent.getNum());
				opponent.isDefeated();
				break;
			case ROCK:
			case SPOCK:
				opponent.Defeated(m_num);
				m_inGame = false;
				break;
			case SCISSORS:
				if (m_num < opponent.getNum())
				{
					m_opponents.push_back(opponent.getNum());
					opponent.isDefeated();
				}
				else
				{
					opponent.Defeated(m_num);
					m_inGame = false;
				}
				break;
			}
		}
		if (m_play == PAPER)
		{
			switch (opponent.getPlay())
			{
			case ROCK:
			case SPOCK:
				m_opponents.push_back(opponent.getNum());
				opponent.isDefeated();
				break;
			case SCISSORS:
			case LIZARD:
				opponent.Defeated(m_num);
				m_inGame = false;
				break;
			case PAPER:
				if (m_num < opponent.getNum())
				{
					m_opponents.push_back(opponent.getNum());
					opponent.isDefeated();
				}
				else
				{
					opponent.Defeated(m_num);
					isDefeated();
					//m_inGame = false;
				}
				break;
			}
		}
		if (m_play == SPOCK)
		{
			switch (opponent.getPlay())
			{
			case SCISSORS:
			case ROCK:
				m_opponents.push_back(opponent.getNum());
				opponent.isDefeated();
				break;
			case PAPER:
			case LIZARD:
				opponent.Defeated(m_num);
				m_inGame = false;
				break;
			case SPOCK:
				if (m_num < opponent.getNum())
				{
					m_opponents.push_back(opponent.getNum());
					opponent.isDefeated();
				}
				else
				{
					opponent.Defeated(m_num);
					m_inGame = false;
				}
				break;
			}
		}
		if (m_play == LIZARD)
		{
			switch (opponent.getPlay())
			{
			case SPOCK:
			case PAPER:
				m_opponents.push_back(opponent.getNum());
				opponent.isDefeated();
				break;
			case ROCK:
			case SCISSORS:
				opponent.Defeated(m_num);
				m_inGame = false;
				break;
			case LIZARD:
				if (m_num < opponent.getNum())
				{
					m_opponents.push_back(opponent.getNum());
					opponent.isDefeated();
				}
				else
				{
					opponent.Defeated(m_num);
					m_inGame = false;
				}
				break;
			}
		}
	}
};

int numOfRounds(int n, int pow = 1)
{
	if (n == 2)
		return pow;
	else
	{
		++pow;
		n /= 2;
		return numOfRounds(n, pow);
	}
}

int main()
{
	int N;
	cin >> N;
	cin.ignore();
	vector<Player> players;
	players.reserve(N);
	// считывание игроков
	for (int i = 0; i < N; i++)
	{
		int NUMPLAYER;
		char SIGNPLAYER;
		cin >> NUMPLAYER >> SIGNPLAYER;
		cin.ignore();
		players.push_back(Player(NUMPLAYER, SIGNPLAYER));
	}
	//здесь rounds число кругов сколько пройдет при данном N
	int rounds = numOfRounds(N);
	for (int i = 0; i < rounds; ++i)
	{
		// игроки играют раунды
		for (int j = 0; j < players.size(); j += 2)
		{
			players[j].playMatch(players[j + 1]);
		}
		int index(0);
		int size = players.size();
		// удаляются проигравшие в данном круге игроки
		for (int i = 0; i < size; ++i)
		{
			if (!players[index].isInGame())
			{
				players.erase(players.begin() + index);
				if (index < 0)
					++index;
			}
			else
				++index;
		}
	}
	// в векторе остался 1 победитель, вывод его номера и списка оппонентов
	cout << players[0].getNum() << endl;
	players[0].printOpponents();

	return 0;
}