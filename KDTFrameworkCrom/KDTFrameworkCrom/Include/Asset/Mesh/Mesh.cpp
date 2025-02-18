#include "Mesh.h"
#include "../../Device.h"

CMesh::CMesh()
{
}

CMesh::~CMesh()
{
	// ���� �Ҵ��� ���� �޸�����.
	size_t Size = mMeshSlot.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(mMeshSlot[i]);
	}
}

bool CMesh::CreateMesh(void* VertexData, int Size, 
	int Count, D3D11_USAGE VertexUsage, 
	D3D11_PRIMITIVE_TOPOLOGY Primitive, 
	void* IndexData, int IndexSize, int IndexCount,
	DXGI_FORMAT Format, D3D11_USAGE IndexUsage)
{
	// Vertex�� ������ �����ϱ� ���� ä���.
	mVertexBuffer.Size = Size;
	mVertexBuffer.Count = Count;
	mVertexBuffer.Data = new char[Size * Count];
	memcpy(mVertexBuffer.Data, VertexData, Size * Count);

	if (!CreateBuffer(&mVertexBuffer.Buffer, D3D11_BIND_VERTEX_BUFFER, VertexData,
		Size, Count, D3D11_USAGE_DEFAULT))
		return false;

	mPrimitive = Primitive;

	// IndexData�� ������ (�⺻������ nullptr�� ������)
	if (IndexData)
	{
		// �޽� ����
		FMeshSlot* Slot = new FMeshSlot;

		Slot->IndexBuffer.Size = Size;
		Slot->IndexBuffer.Count = Count;
		Slot->IndexBuffer.Data = new char[IndexSize * IndexCount];
		memcpy(Slot->IndexBuffer.Data, IndexData, IndexSize * IndexCount);

		if (!CreateBuffer(&Slot->IndexBuffer.Buffer,
			D3D11_BIND_INDEX_BUFFER, IndexData,
			IndexSize, IndexCount, IndexUsage))
		{
			SAFE_DELETE(Slot);
			return false;
		}

		mMeshSlot.push_back(Slot);
	}

	return true;
}

bool CMesh::CreateBuffer(ID3D11Buffer** Buffer, 
	D3D11_BIND_FLAG Flag, void* Data, int Size, 
	int Count, D3D11_USAGE Usage)
{
	D3D11_BUFFER_DESC BufferDesc = {};

	// ������ ����Ʈ ���� ����.
	// �ϳ��� ũ�� * ����
	BufferDesc.ByteWidth = Size * Count;
	BufferDesc.Usage = Usage;
	BufferDesc.BindFlags = Flag;

	if (Usage == D3D11_USAGE_DYNAMIC)
		BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	else if (Usage == D3D11_USAGE_STAGING)
		BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
	
	// ���� ����
	D3D11_SUBRESOURCE_DATA BufferData = {};

	BufferData.pSysMem = Data;
	
	// ������ Data(Vertex Data)�� pSysMem�� �ְ�,
	// Buffer�� ����� pSysMem������ BufferDesc�� ä���ش�.
	if (FAILED(CDevice::GetInstance()->GetDevice()->CreateBuffer(&BufferDesc, &BufferData, Buffer)))
		return false;

	return true;
}
