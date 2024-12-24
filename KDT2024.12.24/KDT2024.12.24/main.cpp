#include <iostream>
#include <vector>

/*
	템플릿의 활용법
	배열 클래스 만들기

	stl(Standard Template Library) : C++에서 제공하는 표준 템플릿 라이브러리이다.
	std namespace 안에 들어가있다.
	템플릿을 이용하기 때문에 원하는 타입을 지정하고 데이터를 저장할 수 있다.
	-------주로 다룰 3가지-------
	- 시퀀스 컨테이너
	1. vector		: 동적배열을 구현해놓은 클래스.
				특징	: 필요에 따라 크기를 늘리거나 줄일 수 있는 배열이다.
					random Access를 지원하여 Index로 접근이 가능하다.
					가장 끝에 추가할 경우 0(1)의 성능을 보여준다.
					중간에 추가/삭제 할 경우 0(n)의 성능을 보여준다.

	2. list			: 
	
	- 연관 컨테이너
	1. unordered_map: 
	---------------------------
*/


class CContainer
{
public:
	CContainer()
	{
		//std::cout << "생성자" << std::endl;
	}

	CContainer(int Num) :
		mNum(Num)
	{
		//std::cout << "인자 생성자" << std::endl;
	}

	CContainer(const CContainer& Con)
	{
		mNum = Con.mNum;
		//std::cout << "복사생성자" << std::endl;
	}

	CContainer(CContainer&& Con)
	{
		mNum = Con.mNum;
		//std::cout << "이동생성자" << std::endl;
	}

	~CContainer()
	{
		//std::cout << "소멸자" << std::endl;
	}

	int	mNum = 0;
};

int main()
{
	std::vector<CContainer> vectorCon;	
	std::vector<int> vectorInt;			// Int 타입을 저장하는 벡터(동적배열)생성.

	// 벡터는 요소추가가 없을 경우 배열크기가
	// 0이다.
	std::cout << "처음 Capacity : " << vectorInt.capacity() << std::endl;

	// push/emplace Back : 둘다 뒤쪽 끝에 추가.
	// push_back은 복사생성자 혹은 이동생성자 둘중 하나가 호출된다.
	//	인자로 들어가는 값이 임시객체일 경우 "이동생성"이 된다.
	int Index = 0;
	vectorInt.push_back(10);			// 이동생성
	vectorInt.push_back(Index);			// 복사생성
	// pop_back은 가장 마지막 배열을 제거한다.
	vectorInt.pop_back();				//
	// clear는 전체 요소를 제거한다.
	vectorInt.clear();
	// size는 추가된 갯수를 얻어온다.
	vectorInt.size();
	// capacity는 배열 전체 개수를 얻어온다.
	vectorInt.capacity();
	// empty는 배열이 비어있을경우 (실제로 추기된게 없으면) true, 아니면 false
	vectorInt.empty();
	// at(인덱스)로도 배열에 접근할 수 있다.
	vectorInt.at(1);
	// front()는 첫번째 요소를 가져온다.
	vectorInt.front();
	// back()은 마지막 요소를 가져온다.
	vectorInt.back();
	// reserve : 백터 공간을 원하는 만큼 늘린다.
	vectorInt.reserve(100);		// 배열 공간을 Index값에 맞게 생성한다.
	// resize : 배열 공간 및 추가된 요소도 이 갯수만큼 한다.
	vectorInt.resize(100);
	// emplace_back : 직접생성방식.
	//인자를 이용하여 이 벡터의 내부 메모리에서 객체 생성을 한다.
	vectorInt.emplace_back(20);			// 내부에서 복사/이동을 하지 않는다.

	for (int i = 0; i < 10; i++)
	{
		vectorInt.push_back(i * 100);
		std::cout << "Size : " << vectorInt.size() << std::endl;
		std::cout << "Capacity : " << vectorInt.capacity() << std::endl;
	}


	/*
		iterator : 각 요소를 차례대로 방문할 수 있게 해주는 기능이다.
				반복자이기 때문에 반복해서 요소를 차례로 방문하여,
				값을 얻어올 수 있고, 수정할 수 있다.
	*/
	// reverse iterator : 뒤에서부터 앞으로 반복하는 용도의 기능.

	// 배열 공간을 원하는만큼 늘린다.
	//vectorInt.reserve(100);
	// 배열 공간도 늘리고 추가된 요소도
	// 이 개수만큼으로 한다.
	vectorInt.resize(100);

	for (int i = 0; i < 10; ++i)
	{
		vectorInt.push_back(i * 100);
		std::cout << "Size : " << vectorInt.size() <<
			", Capacity : " << vectorInt.capacity() <<
			std::endl;
	}

	// 이너클래스 : 클래스안에 클래스를 만듦
	std::vector<int>::iterator iter;
	std::vector<int>::iterator iterEnd = vectorInt.end();

	// begin : 배열의 첫번째 요소를 가지고 있는
	// iterator를 반환한다.
	// end : 배열 마지막요소의 다음을 가지고 있는
	// iterator이다. 명시적으로 끝을 표현하기위해
	// 사용된다.
	for (iter = vectorInt.begin(); iter != iterEnd; iter++)
	{
		// 역참조를 하여 iterator가 가지고
		// 있는 요소의 값을 가져온다.
		std::cout << *iter << std::endl;
	}
		
	// reverse iterator : 뒤에서부터 앞으로[
	// 반복하는 용도로 사용한다.
	std::vector<int>::reverse_iterator iterReverse;
	std::vector<int>::reverse_iterator iterEnd = vectorInt.rend();

	for (iterReverse = vectorInt.rbegin(); iterReverse != iterEnd; iterReverse++)
	{
		std::cout << *iterEnd << std::endl;
	}

	std::vector<int>::const_iterator citer;
	citer = vectorInt.begin();

	iter = vectorInt.insert(iter, 1234);

	iterReverse = vectorInt.begin();
	iterReverse += 100;

	// insert() 기능은 중간 배열에 추가하는 것이다.
	citer = vectorInt.insert(iterReverse, 1020);

	// erase : 벡터의 요소를 제거한다.
	// 인자로 들어간 iterator의 요소를 제거하고,
	// 그 다음요소를 가지고 iterator를 반환.
	vectorInt.erase(iter);

	iter = vectorInt.erase(vectorInt.begin(), iter);

	std::cout << *iter << std::endl;
	
	iterEnd = vectorInt.end();

	for (iter = vectorInt.begin(); iter != iterEnd; iter++)
	{
		std::cout << *iter << std::endl;
	}

	return 0;
}