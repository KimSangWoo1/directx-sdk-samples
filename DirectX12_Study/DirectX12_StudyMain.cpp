#include "pch.h"
#include "DirectX12_StudyMain.h"
#include "Common\DirectXHelper.h"

using namespace DirectX12_Study;
using namespace Windows::Foundation;
using namespace Windows::System::Threading;
using namespace Concurrency;

// DirectX 12 ���ø����̼� ���ø��� ���� ������ https://go.microsoft.com/fwlink/?LinkID=613670&clcid=0x412�� ���� �ֽ��ϴ�.

// ���ø����̼��� �ε�Ǹ� ���ø����̼� �ڻ��� �ε��ϰ� �ʱ�ȭ�մϴ�.
DirectX12_StudyMain::DirectX12_StudyMain()
{
	// TODO: �⺻ ���� timestep ��� �ܿ� �ٸ� ������ �Ϸ��� Ÿ�̸� ������ �����մϴ�.
	// ��: 60FPS ���� timestep ������Ʈ ���� ��� ������ ȣ���մϴ�.
	/*
	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60);
	*/
}

// �������� ����� �ʱ�ȭ�մϴ�.
void DirectX12_StudyMain::CreateRenderers(const std::shared_ptr<DX::DeviceResources>& deviceResources)
{
	// TODO: �� �׸��� �� ������ �ʱ�ȭ�� ��ü�մϴ�.
	m_sceneRenderer = std::unique_ptr<Sample3DSceneRenderer>(new Sample3DSceneRenderer(deviceResources));

	OnWindowSizeChanged();
}

// �����Ӵ� �� �� ���ø����̼� ���¸� ������Ʈ�մϴ�.
void DirectX12_StudyMain::Update()
{
	// ��� ��ü�� ������Ʈ�մϴ�.
	m_timer.Tick([&]()
	{
		// TODO: �� �׸��� �� ������ ������Ʈ �Լ��� ��ü�մϴ�.
		m_sceneRenderer->Update(m_timer);
	});
}

// ���� ���ø����̼� ���¿� ���� ���� �������� �������մϴ�.
// �������� �������Ǿ� ǥ���� �غ� �Ǹ� true�� ��ȯ�մϴ�.
bool DirectX12_StudyMain::Render()
{
	// ó�� ������Ʈ�ϱ� ���� �ƹ��͵� ���������� ������.
	if (m_timer.GetFrameCount() == 0)
	{
		return false;
	}

	// ��� ��ü�� �������մϴ�.
	// TODO: �� �׸��� �� ������ ������ �Լ��� ��ü�մϴ�.
	return m_sceneRenderer->Render();
}

// â�� ũ�Ⱑ ���ϸ�(��: ����̽� ���� ����) ���ø����̼� ���¸� ������Ʈ�մϴ�.
void DirectX12_StudyMain::OnWindowSizeChanged()
{
	// TODO: �� �׸��� �� �������� ũ�� ���� �ʱ�ȭ�� ��ü�մϴ�.
	m_sceneRenderer->CreateWindowSizeDependentResources();
}

// �Ͻ� �ߴ� ���°� �ƴ� ���� �˷� �ݴϴ�.
void DirectX12_StudyMain::OnSuspending()
{
	// TODO: �̰��� ���� �Ͻ� �ߴ� ���� �ٲټ���.

	// �������� ���μ��� ���� ������ �Ͻ� ������ ���� ������ ���� �ֽ��ϴ�. ����
	// ���� �ߴܵ� ��ġ���� ���� �ٽ� ���۵� �� �ֵ��� ���� ��� ���¸� �����ϴ� ���� �����ϴ�. 

	m_sceneRenderer->SaveState();

	// ���ø����̼ǿ��� �ٽ� ����Ⱑ ���� ���� �޸� �Ҵ��� ����ϴ� ���,
	// �ش� �޸𸮸� �������Ͽ� �ٸ� ���ø����̼��� ����� �� �ֵ��� �غ�����.
}

// �� �̻� �Ͻ� �ߴ� ���°� �ƴ� ���� �˷� �ݴϴ�.
void DirectX12_StudyMain::OnResuming()
{
	// TODO: �̰��� ���� �ٽ� ���� ���� �ٲټ���.
}

// �������� �ʿ��� ����̽� ���ҽ��� �������� �˸��ϴ�.
void DirectX12_StudyMain::OnDeviceRemoved()
{
	// TODO: �ʿ��� ���ø����̼� �Ǵ� ������ ���¸� �����ϰ� �������� �������ϼ���.
	// �� �� �̻� ��ȿ���� ���� ���ҽ��Դϴ�.
	m_sceneRenderer->SaveState();
	m_sceneRenderer = nullptr;
}
