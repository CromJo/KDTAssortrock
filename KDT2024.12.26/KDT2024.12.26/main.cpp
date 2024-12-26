#include <iostream>

// 탐색용 전처리기
#include <unordered_map>
#include <map>			// 이진트리 방식
#include <set>			// 이진트리 방식

/*
	unordered_map, map, set 셋다 탐색을 위해 제공되는 알고리즘이다.
	많은 데이터가 있을 경우 탐색을 빠르게 해줄 수 있다.
	데이터는 셋다 key와 value로 구성이 된다.
	
	-- 이진트리 방식 --
	key : 탐색을 위한 값이다.
	value : 실제 저장하고자 하는 값이다.
	map, set
		1. 균형 이진트리로 구성되어 있다.
		2. 삽입/삭제가 느리다. 
			실시간으로 추가삭제가 많이 일어나는 곳에서는 사용이 어렵다.
			로딩단계에서 미리 가지고 있게 하고 탐색만 하는 경우 유용하다.
		3. 데이터를 추가하면 자동으로 정렬이 된다.
	unordered_map : 
		1. 해시테이블로 구성되어있다. (map보다 후에 나왔다.)
		2. 메모리를 많이 사용한다.
		3. 삽입/삭제/탐색의 평균 시간복잡도는 0(1)(매우 빠름)이다.
		4. 해시 충돌이 많이 발생할 경우 0(n)(매우 느림)이 될 수 있다.
		5. 자동으로 정렬이 되지 않는다.

	map, set, unordred_map 모두 key가 중복되는 것을 허용하지 않는다. 
	
	key 중복이 필요한 경우,
		1. multi_map, multi_set, unordered_multimap을 사용한다.

	boost library
*/
int main()
{
	/*
		3가지 방식 모두 메모리의 크기가 서로 다르다.
		1. const char* cText = "abc";
		2. char Text[4] = {};
			strcpy_s(Text, "abc");

		cText == Text는 false이다. 
		왜냐하면 서로의 메모리주소가 다르기 때문에
		배열은 자동으로 메모리주소를, 포인터는 메모리주소를 가리키는데,
		서로의 "값"만 같을 뿐 메모리주소 비교를 하는 구문이기에 false가 나올 수 밖에 없다.
	*/

	// 우리가 직접 해쉬함수를 정의할 필요는 없다.
	std::unordered_map<std::string, int> IntMap;

	// 삽입 기능 (insert)
	//IntMap.insert(std::pair("aaa", 10));
	IntMap.insert({"aaa", 10});

	// key를 이용하여 랜덤액세스 연산자를 지원한다.
	// key가 있으면 Value를 리턴.
	// key가 없으면 ket를 생성 및 대입해주는 값을 Value로 설정.
	IntMap["aaa"];

	IntMap["bbb"] = 1010;
	std::cout << IntMap["bbb"] << std::endl;
	std::cout << IntMap["ccc"] << std::endl;

	// pair : key, value를 가지는 데이터 구조
	IntMap.insert(std::make_pair("ddd", 2020));

	// 탐색 기능 (find)
	// find : 
	//		1. key값을 넣을 경우 key, value를 가지고 있는 iterator를 반환한다.
	//		2. key값이 없을 경우 end()를 반환한다.
	std::unordered_map<std::string, int>::iterator iter = IntMap.find("1234");
	
	// 속도가 매우 빠르다. 
	if (iter == IntMap.end())
	{
		std::cout << "탐색할 값이 없습니다." << std::endl;
	}
	else
	{
		std::cout << "Key : " << iter->first << "\t Value : " << iter->second << std::endl;
		iter = IntMap.erase(iter);
	}

	std::unordered_map<std::string, int>::iterator iterEnd = IntMap.end();

	for (iter = IntMap.begin(); iter != iterEnd; iter++)
	{
		std::cout << "Key : " << iter->first << "\t Value : " << iter->second << std::endl;
	}

	for (const std::pair<std::string, int>& pair : IntMap)
	{
		std::cout << "Key : " << pair->first << "\t Value : " << pair->second << std::endl;
	}

	// 제거 기능(clear)
	// IntMap.clear();

	// 특정 키가 있는지 확인하는 용도이다.
	// 없으면 0 있으면 1 반환
	IntMap.count("aaa") > 0;


	std::unordered_multimap<std::string, int> IntMultiMap;

	IntMultiMap.insert({ "aaa", 20 });
	IntMultiMap.insert({ "bbb", 33 });
	IntMultiMap.insert({ "aaa", 58 });
	// auto : 자동으로 맞는 자료형을 설정해주는 자료형 (성능 안좋음)
	auto range = IntMultiMap.equal_range("aaa");

	for (auto iter = range.first; iter != range.second; iter++)
	{
		std::cout << "Key : " << iter->first << ", Value : " << iter->second << std::endl;
	}

	std::cout << typeid(range).name() << std::endl;

	// multimap은 find를 하면 키가 여러개 있을 경우 첫번째 키의 pair를 찾아온다.
	auto iterFind = IntMultiMap.find("aaa");

	for (auto MultiPair : IntMultiMap)
	{
		std::cout << "Key : " << MultiPair.first << ", Value : " << MultiPair.second << std::endl;
	}

	std::cout << IntMultiMap.count("aaa") << std::endl;

	//IntMultiMap.erase(iterFind);		// 인자로 받아온 데이터 하나만 제거.
	//IntMultiMap.erase("aaa");			// aaa로 되어있는 모든 요소를 제거.

	std::cout << IntMultiMap.count("aaa") << std::endl;
	//std::cout << IntMultiMap["aaa"] << std::endl;		// 이런 방식은 지원하지 않는다.



	return 0;
}