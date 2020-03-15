#ifndef EIGHTQUEUE_H
#define EIGHTQUEUE_H

#include"LinkList.h"
using namespace std;  

namespace DSL 
{
	template <int SIZE>
	class EightQueuen : public TopClass
	{
	protected:
		enum{ N = SIZE + 2};
		struct cell : public TopClass
		{
			cell(int x = 0, int y = 0) : px(x), py(y) {}
			int px;
			int py;
		};	

		int chessboard[N][N];
		LinkList<cell> m_solution;
		int m_count = 0;

		void init()
		{
			for(int x = 0; x < N; x += N - 1)
			{
				for(int y = 0; y < N ; y++)
				{
					chessboard[x][y] = 2;
					chessboard[y][x] = 2;
				}
			}
			for(int x = 1; x < N - 1; x++)
			{
				for(int y = 1; y < N - 1; y++)
				{
					chessboard[x][y] = 0;
				}
			}
		}
		
		void show_resolution()
		{
			for(m_solution.move(0); !m_solution.end(); m_solution.next())
			{
				cout << "(" << m_solution.current().px << "," << m_solution.current().py << ") " ;
			}
			cout << endl;

			for(int y = 0; y < N; y++)
			{
				for(int x = 0; x < N; x++)
				{
					cout << chessboard[x][y];
				}
				cout << endl;
			}
			cout << endl;
		}

		bool cell_check(int x, int y)
		{
			bool ret = 1, flag = 1,flag1,flag2,flag3;
			int temp_x = x, temp_y = y;
			int dir_1 = 0, dir_2 = 0, dir_3 = 0;

			do{
				temp_x = temp_x + (-1);
				temp_y = temp_y + (-1);
				flag = (chessboard[temp_x][temp_y] == 0);
			}while(flag);
			flag1 = (chessboard[temp_x][temp_y] == 2);

			temp_x = x;
			temp_y = y;
			do{
				temp_x = temp_x + (0);
				temp_y = temp_y + (-1);
				flag = (chessboard[temp_x][temp_y] == 0);
			}while(flag);
			flag2 = (chessboard[temp_x][temp_y] == 2);

			temp_x = x;
			temp_y = y;
			do{
				temp_x = temp_x + (1);
				temp_y = temp_y + (-1);
				flag = (chessboard[temp_x][temp_y] == 0);
			}while(flag);
			flag3 = (chessboard[temp_x][temp_y] == 2);

		    return (flag1 && flag2 && flag3);
		}

		void line_check(int y)
		{
			if(y <= SIZE)
			{
				for(int x = 1; x <= SIZE; x++)
				{
					if(cell_check(x,y))
					{
						chessboard[x][y] = 1;
						m_solution.insert(cell(x,y));
						line_check(y + 1);
						chessboard[x][y] = 0;
						m_solution.remove(m_solution.length() - 1);
					}
				}
			}
			else
			{
				show_resolution();
				m_count++;
			}
		}

	public:
		EightQueuen()
		{
			init();
		}

		void process()
		{
			line_check(1);
			cout << "Total Solution = " << m_count << endl;
		}
	};
}
#endif
