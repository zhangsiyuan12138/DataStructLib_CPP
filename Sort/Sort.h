#ifndef SORT_H
#define SORT_H

#include"TopClass.h"
#include"Array.h"

namespace DSL
{
	class Sort : public TopClass
	{
	private:
		Sort(); // ˽�л����캯������ֹ��������
		Sort(const Sort&);
		Sort& operator = (const Sort&);

		template <typename T>
		static void swap(T& a,T& b)
		{
			T c(a);
			a = b;
			b = c;
		}

		template <typename T>
		static void merge_sort_core(T array[], T temp_array[], int begin, int end, bool ascned = ture)
		{
			if(begin == end)
			{
				return;
			}
			else
			{
				//�ָ�
				int mid = (begin + end) / 2;
				merge_sort_core(array, temp_array, begin, mid, ascned);
				merge_sort_core(array, temp_array, mid + 1, end, ascned);
				//�ϲ�
				int x = begin, y = mid + 1, z = begin;
				while(x <= mid && y <= end)
				{
					if(array[x] < array[y])
					{
						temp_array[z++] = array[x++];
					}
					else
					{
						temp_array[z++] = array[y++];
					}
				}
				while(x <= mid)
				{
					temp_array[z++] = array[x++];
				}
				while(y <= end)
				{
					temp_array[z++] = array[y++];
				}
				for(z = begin; z <= end; z++)
				{
					array[z] = temp_array[z];
				}
			}
		}

		template <typename T>
		static void quick_sort_core(T array[], int begin, int end, bool ascned = ture)
		{
			//ȷ����׼ֵ��λ��
			int base_pos = 0, base_value = array[begin], begin_slide = begin, end_slide = end;
			while(begin_slide < end_slide)
			{
				while(begin_slide < end_slide && ascned ? base_value  < array[end_slide] : base_value  > array[end_slide])
				{
					--end_slide;
				}
				swap(array[begin_slide], array[end_slide]);
				while(begin_slide < end_slide && ascned ? base_value >= array[begin_slide] : base_value <= array[begin_slide])
				{
					++begin_slide;
				}
				swap(array[begin_slide], array[end_slide]);
			}
			array[begin_slide] = base_value;
			base_pos = begin_slide;
			// ��������	
			quick_sort_core(array, begin, (base_pos - 1), ascned);
			quick_sort_core(array, base_pos + 1, end, ascned);
		}

	public:
		template <typename T>
		static void select_sort(T array[], int len, bool ascend = false)
		{
			for(int x = 0; x < len; x++)
			{
				int min = x; 
				for(int y = x + 1; y < len; y++)
				{
					if(ascend ? array[min] > array[y] : array[min] < array[y]) //����< ����>
						min = y;
				}
				if(min != x)
					swap(array[x],array[min]); //���ȶ�����
			}
		}

		template <typename T>
		static void insert_sort(T array[], int len, bool ascend = false)
		{
			for(int x = 1; x < len; x++)
			{
				int z = x;
				T temp = array[z];
				for(int y = x - 1; (y >= 0) && (ascend ? array[y] > temp: array[y] < temp); y--)
				{
					array[y + 1] = array[y]; //�ȶ�����
					z = y;
				}
				if(z != x)
				{
					array[z] = temp;
				}
			}
		}

		template <typename T>
		static void bubble_sort(T array[], int len, bool ascend = false)
		{
			bool state = ture;
			for(int x = 0; x < len && state; x++) //ĳ��Ԫ���޷�ǰ��Ԫ�ض�������ģ���������
			{
				state = false;
				for(int y = len - 1; y > x; y--)
				{
					if(ascend ? array[y] > array[y - 1] : array[y] < array[y - 1])
					{
						swap(array[y],array[y - 1]);
						state = ture; 
					}
				}
			}
		}

		template <typename T>
		static void shell_sort(T array[], int len, bool ascend = false)
		{
			int d = len;
			do
			{
				d = d / 3 + 1; //???
				for(int x = d ; x < len; x += d)
				{
					int z = x;
					T temp = array[z];
					for(int y = x - d; (y >= 0) && (ascend ? array[y] > temp: array[y] < temp); y -= d)
					{
						array[y + d] = array[y]; //���ȶ�����
						z = y;
					}
					if(z != x)
					{
						array[z] = temp;
					}
				}
			}
			while(d > 1);
		}

		template <typename T>
		static void merge_sort(T array[], int len, bool ascned = ture)
		{
			T* temp_array = new T[len];
			merge_sort_core(array, temp_array, 0, len - 1, ture);
			delete[] temp_array;
		}

		template <typename T>
		static void quick_sort(T array[], int len, bool ascned = ture)
		{
			quick_sort_core(array, 0, len - 1, ascned);
		}

		
		// ֧��������
		template <typename T>
		static void select_sort(Array<T>& array, bool ascned = ture)
		{
			select_sort(array.array(), array.length(), ascned);
		}

		template <typename T>
		static void insert_sort(Array<T>& array, bool ascned = ture)
		{
			insert_sort(array.array(), array.length(), ascned);
		}

		template <typename T>
		static void bubble_sort(Array<T>& array, bool ascned = ture)
		{
			bubble_sort(array.array(), array.length(), ascned);
		}

		template <typename T>
		static void shell_sort(Array<T>& array, bool ascned = ture)
		{
			shell_sort(array.array(), array.length(), ascned);
		}

		template <typename T>
		static void merge_sort(Array<T>& array, bool ascned = ture)
		{
			merge_sort(array.array(), array.length(), ascned);
		}

		template <typename T>
		static void quick_sort(Array<T>& array, bool ascned = ture)
		{
			quick_sort(array.array(), array.length(), ascned);
		}

		
	};
}


#endif
