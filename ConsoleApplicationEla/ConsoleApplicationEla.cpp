#include <iostream>
#include <windows.h>
#include <list>
#include <conio.h>


bool operator==(COORD const& one, COORD const& other)
{
	return one.X == other.X && one.Y == other.Y;
}

COORD& operator+=(COORD& one, COORD const& other)
{
	one.X += other.X;
	one.Y += other.Y;
	return one;
}

COORD& operator-=(COORD& one, COORD const& other)
{
	one.X -= other.X;
	one.Y -= other.Y;
	return one;
}

COORD operator-(COORD const& one)
{
	COORD tmp;
	tmp.X = -one.X;
	tmp.Y = -one.Y;
	return tmp;
}

using namespace std;

HANDLE handle = nullptr;

char GetConsoleChar(short xPos, short yPos)
{
	if (!handle)
	{
		return 0;
	}
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
	if (!GetConsoleScreenBufferInfo(handle, &screenBufferInfo))
	{
		printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError());
		return 0;
	}

	char buf[2];
	COORD pos = { xPos, yPos };
	DWORD num_read;
	if (!ReadConsoleOutputCharacter(handle, (LPTSTR)buf, 1, pos, (LPDWORD)&num_read))
	{
		cout << "\7Error reading console.\n";
	}
	return buf[0];
}

bool Tick(COORD& coord, COORD& direction, COORD& coordTail, std::list<COORD>& tailArray, char ooo);

int main()
{
	for (; ;)
	{
		system("mode con cols=51 lines=31"); // установка размеров окна консоли
		MoveWindow(GetConsoleWindow(), 600, 250, 600, 600, true); // установка стартовой позиции окна консоли (600 и 250 - это пиксели
		// относительно верхнего левого угла монитора
		COORD coord; // объект для хранения координат
		handle = GetStdHandle(STD_OUTPUT_HANDLE); // создание хендла потока вывода
		CONSOLE_CURSOR_INFO ConCurInf;
		// спрячем курсор
		ConCurInf.dwSize = 10;
		ConCurInf.bVisible = FALSE;
		SetConsoleCursorInfo(handle, &ConCurInf);

		for (int ii = 0; ii < 35; ++ii)
		{
			coord.X = 0;
			coord.Y = ii;
			SetConsoleCursorPosition(handle, coord);
			cout << "X";
		}

		for (int ii = 0; ii < 73; ++ii)
		{
			coord.X = ii;
			coord.Y = 0;
			SetConsoleCursorPosition(handle, coord);
			cout << "X";
		}

		for (int ii = 0; ii < 35; ++ii)
		{
			coord.X = 72;
			coord.Y = ii;
			SetConsoleCursorPosition(handle, coord);
			cout << "X";
		}

		for (int ii = 0; ii < 73; ++ii)
		{
			coord.X = ii;
			coord.Y = 33;
			SetConsoleCursorPosition(handle, coord);
			cout << "X";
		}
		for (int ii = 1; ii < 72; ++ii)
		{
			coord.X = ii;
			coord.Y = 34;
			SetConsoleCursorPosition(handle, coord);
			cout << "X";
		}

		for (int ii = 1; ii < 35; ++ii)
		{
			coord.X = 71;
			coord.Y = ii;
			SetConsoleCursorPosition(handle, coord);
			cout << "X";
		}
		for (int ii = 1; ii < 35; ++ii)
		{
			coord.X = 1;
			coord.Y = ii;
			SetConsoleCursorPosition(handle, coord);
			cout << "X";
		}
		for (int ii = 1; ii < 73; ++ii)
		{
			coord.X = ii;
			coord.Y = 1;
			SetConsoleCursorPosition(handle, coord);
			cout << "X";
		}

		/* initialize random seed: */
		srand(static_cast<unsigned int>(time(NULL)));

		for (int ii = 0; ii < 5000; ++ii)
		{
			coord.X = rand() % 69 + 2;
			coord.Y = rand() % 31 + 2;
			SetConsoleCursorPosition(handle, coord);
			cout << "*";
		}
		// *********** head1 initialization
		coord.X = 17;
		coord.Y = 17;
		SetConsoleCursorPosition(handle, coord);
		cout << "O";

		COORD direction = { 1, 1 };

		COORD coordTail = coord; // объект для хранения координат хвоста
		std::list<COORD> tailArray;
		tailArray.push_back(direction);
		// *********** head2 initialization
		COORD coord2;
		coord2.X = 16;
		coord2.Y = 17;
		SetConsoleCursorPosition(handle, coord2);
		cout << "O";

		COORD direction2 = { 1, 1 };

		COORD coordTail2 = coord2; // объект для хранения координат хвоста
		std::list<COORD> tailArray2;
		tailArray2.push_back(direction2);
		// ************* end head2 initialization

		bool isLeftPressed = false;
		bool isRightPressed = false;

		for (; ;)
		{
			bool isLocalLeftPressed = false;
			bool isLocalRightPressed = false;
			bool isLocalLeftUnPressed = false;
			bool isLocalRightUnPressed = false;

			for (int ii = 0; ii < 100000; ++ii)
			{
				if (GetAsyncKeyState(VK_LEFT))
				{
					isLocalLeftPressed = true;
				}
				else
				{
					isLocalLeftUnPressed = true;
				}
				if (GetAsyncKeyState(VK_RIGHT))
				{
					isLocalRightPressed = true;
				}
				else
				{
					isLocalRightUnPressed = true;
				}
			}

			bool isLeftPressedResult = false;
			if (isLeftPressed)
			{
				if (isLocalLeftUnPressed)
				{
					if (GetAsyncKeyState(VK_LEFT))
					{
						isLeftPressedResult = true;
					}
					else
					{
						isLeftPressed = false;
					}
				}
			}
			else
			{
				if (isLocalLeftPressed)
				{
					isLeftPressedResult = true;
				}
			}

			bool isRightPressedResult = false;
			if (isRightPressed)
			{
				if (isLocalRightUnPressed)
				{
					if (GetAsyncKeyState(VK_RIGHT))
					{
						isRightPressedResult = true;
					}
					else
					{
						isRightPressed = false;
					}
				}
			}
			else
			{
				if (isLocalRightPressed)
				{
					isRightPressedResult = true;
				}
			}

			if (isLeftPressedResult)
			{
				isLeftPressed = true;

				if (direction == COORD({ -1, -1 }))
				{
					direction = { -1, 1 };
				}
				else if (direction == COORD({ 1, -1 }))
				{
					direction = { -1, -1 };
				}
				else if (direction == COORD({ 1, 1 }))
				{
					direction = { 1, -1 };
				}
				else if (direction == COORD({ -1, 1 }))
				{
					direction = { 1, 1 };
				}
				direction2 = direction;
			}
			else if (isRightPressedResult)
			{
				isRightPressed = true;

				if (direction == COORD({ -1, -1 }))
				{
					direction = { 1, -1 };
				}
				else if (direction == COORD({ 1, -1 }))
				{
					direction = { 1, 1 };
				}
				else if (direction == COORD({ 1, 1 }))
				{
					direction = { -1, 1 };
				}
				else if (direction == COORD({ -1, 1 }))
				{
					direction = { -1, -1 };
				}

				direction2 = direction;
			}
			bool ret1 = Tick(coord, direction, coordTail, tailArray, 'O');
			bool ret2 = Tick(coord2, direction2, coordTail2, tailArray2, 'O');
			if (tailArray.size() < tailArray2.size())
			{
				tailArray.push_front(tailArray.front());
				coordTail -= tailArray.front();
			}
			else if (tailArray.size() > tailArray2.size())
			{
				tailArray2.push_front(tailArray2.front());
				coordTail2 -= tailArray2.front();
			}

			SetConsoleCursorPosition(handle, { 31, 0 });
			cout << " lenght: " << tailArray.size() << " ";

			if ((false == ret1 || false == ret2))
			{
				for (int ii = 2; ii < 33; ++ii)
				{
					coord.X = 2;
					coord.Y = ii;
					SetConsoleCursorPosition(handle, coord);
					cout << "                                                                     ";
				}


				coord.X = 30;
				coord.Y = 17;
				SetConsoleCursorPosition(handle, coord);
				cout << " GAME OVER ";
				break;
			}

			//Sleep(150);// задержка в миллисекундах
		}

		// ========================================
		// ждём нажатие любой клавиши
		Sleep(1000);// задержка в миллисекундах
		while (_kbhit())
		{
			_getch();
		}

		for (; ;)
		{
			if (_kbhit())
			{
				break;
			}
			Sleep(1);// задержка в миллисекундах
		}
		// конец блока ждём нажатие любой клавиши
		// ========================================
	}
	

	return 0;
}

bool Tick(COORD& coord, COORD& direction, COORD& coordTail, std::list<COORD>& tailArray, char ooo)
{
	if ('X' == GetConsoleChar(coord.X + direction.X, coord.Y + direction.Y))
	{
		if (('X' != GetConsoleChar(coord.X + direction.X, coord.Y)) && ('X' != GetConsoleChar(coord.X, coord.Y + direction.Y)))
		{
			direction = -direction;
		}
		else if (('X' == GetConsoleChar(coord.X + direction.X, coord.Y)) && ('X' == GetConsoleChar(coord.X, coord.Y + direction.Y)))
		{
			direction = -direction;
			return false;
		}
		else if (('X' != GetConsoleChar(coord.X + direction.X, coord.Y)) && ('X' == GetConsoleChar(coord.X, coord.Y + direction.Y)))
		{
			direction.Y = -direction.Y;
		}
		else if (('X' == GetConsoleChar(coord.X + direction.X, coord.Y)) && ('X' != GetConsoleChar(coord.X, coord.Y + direction.Y)))
		{
			direction.X = -direction.X;
		}
	}
	coord += direction;
	if ('O' == GetConsoleChar(coord.X, coord.Y))
	{
		return false;
	}
	// tail
	tailArray.push_back(direction);
	if ('*' != GetConsoleChar(coord.X, coord.Y))
	{
		SetConsoleCursorPosition(handle, coordTail);
		cout << " ";
		tailArray.pop_front();
		coordTail += tailArray.front();
	}
	// head
	SetConsoleCursorPosition(handle, coord);
	cout << ooo;
	return true;
}

