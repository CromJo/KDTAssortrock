#include "Mesh.h"
#include "../../Device.h"

CMesh::CMesh()
{
}

CMesh::~CMesh()
{
	// 동적 할당을 위한 메모리제거.
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
	// Vertex는 무조건 있으니까 먼저 채운다.
	mVertexBuffer.Size = Size;
	mVertexBuffer.Count = Count;
	mVertexBuffer.Data = new char[Size * Count];
	memcpy(mVertexBuffer.Data, VertexData, Size * Count);

	if (!CreateBuffer(&mVertexBuffer.Buffer, D3D11_BIND_VERTEX_BUFFER, VertexData,
		Size, Count, D3D11_USAGE_DEFAULT))
		return false;

	mPrimitive = Primitive;

	// IndexData가 있으면 (기본적으로 nullptr로 되있음)
	if (IndexData)
	{
		// 메쉬 생성
		FMeshSlot* Slot = new FMeshSlot;

		Slot->IndexBuffer.Size = IndexSize;
		Slot->IndexBuffer.Count = IndexCount;
		Slot->IndexBuffer.Data = new char[IndexSize * IndexCount];
		Slot->IndexBuffer.Format = Format;
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

	// 버퍼의 바이트 수를 지정.
	// 하나의 크기 * 개수
	BufferDesc.ByteWidth = Size * Count;
	BufferDesc.Usage = Usage;
	BufferDesc.BindFlags = Flag;

	if (Usage == D3D11_USAGE_DYNAMIC)
		BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	else if (Usage == D3D11_USAGE_STAGING)
		BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
	
	// 버퍼 생성
	D3D11_SUBRESOURCE_DATA BufferData = {};

	BufferData.pSysMem = Data;
	
	// 위에서 Data(Vertex Data)를 pSysMem에 넣고,
	// Buffer를 만들고 pSysMem정보로 BufferDesc를 채워준다.
	if (FAILED(CDevice::GetInstance()->GetDevice()->CreateBuffer(&BufferDesc, &BufferData, Buffer)))
		return false;

	return true;
}

void CMesh::Render()
{
	unsigned int Stride = mVertexBuffer.Size;
	unsigned int Offset = 0;

	// 그려줄 도형 타입 지정
	CDevice::GetInstance()->GetContext()->
		IASetPrimitiveTopology(mPrimitive);

	// Vertex Buffer를 지정.
	CDevice::GetInstance()->GetContext()->
		IASetVertexBuffers(0, 1, &mVertexBuffer.Buffer,
			&Stride, &Offset);

	size_t SlotCount = mMeshSlot.size();

	// 인덱스 버퍼가 있을 때와 없을 때를 나누어 출력
	if (SlotCount > 0)
	{
		for (size_t i = 0; i < SlotCount; ++i)
		{
			// 출력에 사용할 인덱스버퍼 지정
			CDevice::GetInstance()->GetContext()->
				IASetIndexBuffer(mMeshSlot[i]->IndexBuffer.Buffer,
				mMeshSlot[i]->IndexBuffer.Format, 0);
			
			// 인덱스를 참고하여 화면에 도형 그림.
			CDevice::GetInstance()->GetContext()->DrawIndexed(mMeshSlot[i]->
				IndexBuffer.Count, 0, 0);
		}
	}
	else
	{
		// 별표시

		CDevice::GetInstance()->GetContext()->
			IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
		CDevice::GetInstance()->GetContext()->
			Draw(mVertexBuffer.Count, 0);
	}
}
