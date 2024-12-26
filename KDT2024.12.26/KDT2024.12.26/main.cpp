#include <iostream>

// Ž���� ��ó����
#include <unordered_map>
#include <map>			// ����Ʈ�� ���
#include <set>			// ����Ʈ�� ���

/*
	unordered_map, map, set �´� Ž���� ���� �����Ǵ� �˰����̴�.
	���� �����Ͱ� ���� ��� Ž���� ������ ���� �� �ִ�.
	�����ʹ� �´� key�� value�� ������ �ȴ�.
	
	-- ����Ʈ�� ��� --
	key : Ž���� ���� ���̴�.
	value : ���� �����ϰ��� �ϴ� ���̴�.
	map, set
		1. ���� ����Ʈ���� �����Ǿ� �ִ�.
		2. ����/������ ������. 
			�ǽð����� �߰������� ���� �Ͼ�� �������� ����� ��ƴ�.
			�ε��ܰ迡�� �̸� ������ �ְ� �ϰ� Ž���� �ϴ� ��� �����ϴ�.
		3. �����͸� �߰��ϸ� �ڵ����� ������ �ȴ�.
	unordered_map : 
		1. �ؽ����̺�� �����Ǿ��ִ�. (map���� �Ŀ� ���Դ�.)
		2. �޸𸮸� ���� ����Ѵ�.
		3. ����/����/Ž���� ��� �ð����⵵�� 0(1)(�ſ� ����)�̴�.
		4. �ؽ� �浹�� ���� �߻��� ��� 0(n)(�ſ� ����)�� �� �� �ִ�.
		5. �ڵ����� ������ ���� �ʴ´�.

	map, set, unordred_map ��� key�� �ߺ��Ǵ� ���� ������� �ʴ´�. 
	
	key �ߺ��� �ʿ��� ���,
		1. multi_map, multi_set, unordered_multimap�� ����Ѵ�.

	boost library
*/
int main()
{
	/*
		3���� ��� ��� �޸��� ũ�Ⱑ ���� �ٸ���.
		1. const char* cText = "abc";
		2. char Text[4] = {};
			strcpy_s(Text, "abc");

		cText == Text�� false�̴�. 
		�ֳ��ϸ� ������ �޸��ּҰ� �ٸ��� ������
		�迭�� �ڵ����� �޸��ּҸ�, �����ʹ� �޸��ּҸ� ����Ű�µ�,
		������ "��"�� ���� �� �޸��ּ� �񱳸� �ϴ� �����̱⿡ false�� ���� �� �ۿ� ����.
	*/

	// �츮�� ���� �ؽ��Լ��� ������ �ʿ�� ����.
	std::unordered_map<std::string, int> IntMap;

	// ���� ��� (insert)
	//IntMap.insert(std::pair("aaa", 10));
	IntMap.insert({"aaa", 10});

	// key�� �̿��Ͽ� �����׼��� �����ڸ� �����Ѵ�.
	// key�� ������ Value�� ����.
	// key�� ������ ket�� ���� �� �������ִ� ���� Value�� ����.
	IntMap["aaa"];

	IntMap["bbb"] = 1010;
	std::cout << IntMap["bbb"] << std::endl;
	std::cout << IntMap["ccc"] << std::endl;

	// pair : key, value�� ������ ������ ����
	IntMap.insert(std::make_pair("ddd", 2020));

	// Ž�� ��� (find)
	// find : 
	//		1. key���� ���� ��� key, value�� ������ �ִ� iterator�� ��ȯ�Ѵ�.
	//		2. key���� ���� ��� end()�� ��ȯ�Ѵ�.
	std::unordered_map<std::string, int>::iterator iter = IntMap.find("1234");
	
	// �ӵ��� �ſ� ������. 
	if (iter == IntMap.end())
	{
		std::cout << "Ž���� ���� �����ϴ�." << std::endl;
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

	// ���� ���(clear)
	// IntMap.clear();

	// Ư�� Ű�� �ִ��� Ȯ���ϴ� �뵵�̴�.
	// ������ 0 ������ 1 ��ȯ
	IntMap.count("aaa") > 0;


	std::unordered_multimap<std::string, int> IntMultiMap;

	IntMultiMap.insert({ "aaa", 20 });
	IntMultiMap.insert({ "bbb", 33 });
	IntMultiMap.insert({ "aaa", 58 });
	// auto : �ڵ����� �´� �ڷ����� �������ִ� �ڷ��� (���� ������)
	auto range = IntMultiMap.equal_range("aaa");

	for (auto iter = range.first; iter != range.second; iter++)
	{
		std::cout << "Key : " << iter->first << ", Value : " << iter->second << std::endl;
	}

	std::cout << typeid(range).name() << std::endl;

	// multimap�� find�� �ϸ� Ű�� ������ ���� ��� ù��° Ű�� pair�� ã�ƿ´�.
	auto iterFind = IntMultiMap.find("aaa");

	for (auto MultiPair : IntMultiMap)
	{
		std::cout << "Key : " << MultiPair.first << ", Value : " << MultiPair.second << std::endl;
	}

	std::cout << IntMultiMap.count("aaa") << std::endl;

	//IntMultiMap.erase(iterFind);		// ���ڷ� �޾ƿ� ������ �ϳ��� ����.
	//IntMultiMap.erase("aaa");			// aaa�� �Ǿ��ִ� ��� ��Ҹ� ����.

	std::cout << IntMultiMap.count("aaa") << std::endl;
	//std::cout << IntMultiMap["aaa"] << std::endl;		// �̷� ����� �������� �ʴ´�.



	return 0;
}