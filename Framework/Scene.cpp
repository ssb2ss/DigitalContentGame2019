#include "stdafx.h"
#include "Scene.h"
#include "Framework.h"

Scene* Scene::currentScene;
Scene* Scene::nextScene;

Scene::Scene(): resourceManager(new ResourceManager())	//�����Ҵ�
{
}

Scene::~Scene()
{
	//Scene�� ����Ǿ��� �� ȣ��Ǵ� �Ҹ���
	//gameObjectList (��� ������Ʈ)�� ����
	for (auto& i : gameObjectList)
	{
		SAFE_DELETE(i);
	}

	//���ӿ�����Ʈ����Ʈ�� ����������Ʈ�� ���� ������ ��������
	//��� delete�� �����̹Ƿ�
	//����Ʈ�� ����ִ� clear�Լ��� ����Ʈ�� ����ֱ⸸ ��.
	gameObjectList.clear();
	renderableList.clear();
	SAFE_DELETE(resourceManager);
}

void Scene::SwapScene()
{
	if (!nextScene)
		return;

	SAFE_DELETE(currentScene);
	currentScene = nextScene;
	nextScene = nullptr;

	currentScene->Initialize();
}

void Scene::ChangeScene(Scene* nextScene)
{
	Scene::nextScene = nextScene;
}

Scene& Scene::GetCurrentScene()
{
	return *Scene::currentScene;
}

void Scene::Update()
{
	//��� ������Ʈ�� Update�� ����
	for (auto& i : gameObjectList)	
		if(i->GetActive())
			i->Update();

	//LateUpdate ����
	for (auto& i : gameObjectList)
		if (i->GetActive())
			i->LateUpdate();

	//���� ��û���� ������Ʈ�� ������.
	auto i = destroyedObjectList.begin();
	while (i != destroyedObjectList.end())
	{
		(*i)->OnDestroy();
		gameObjectList.remove(*i);
		renderableList.remove(*i);
		GameObject* t = *i;
		SAFE_DELETE(t);
		destroyedObjectList.remove(*i);
		i = destroyedObjectList.begin();
	}
	destroyedObjectList.clear();
}

void Scene::Render()
{
	//�̱��� ����, Getter
	//d2dapp�� rendertarget�� �޾ƿ�
	D2DApp& d2dapp = Framework::GetInstance().GetD2DApp();
	ID2D1HwndRenderTarget& renderTarget = Framework::GetInstance().GetD2DApp().GetRenderTarget();

	
	d2dapp.BeginRender();//���� ����	
	for (int layer = 0; layer <= 4; layer++)
		for (auto& i : renderableList)
			if (i->GetActive() && i->renderer->GetLayer() == layer)
				i->renderer->Render(renderTarget, *i->transform);
	d2dapp.EndRender();//���� ����
}

GameObject* Scene::PushBackGameObject(GameObject* gameObject)
{
	//���� ������Ʈ�� �������
	gameObjectList.push_back(gameObject);
	//�������� �̹����� �������
	//�������� ����Ʈ�� �������
	if (gameObject->renderer->GetInitialized())
	{
		renderableList.push_back(gameObject);
	}
	return gameObject;//���� ���ӿ�����Ʈ�� �״�� ��ȯ
}

void Scene::Destroy(GameObject* o)
{
	//������ ������Ʈ ����Ʈ�� �������
	destroyedObjectList.push_back(o);
}


ResourceManager& Scene::GetResourceManager()
{
	return *resourceManager;
}
