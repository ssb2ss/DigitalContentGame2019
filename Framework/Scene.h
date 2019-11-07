#pragma once
#include "GameObject.h"
#include "Renderer.h"
#include "stdafx.h"
#include "GameObject.h"
#include "ResourceManager.h"

//����� ��ü�� ������ Scene��ü�Դϴ�.
//Scene�� ��ӹ��� ��ü�� ���� �ڽŸ��� Scene�� ������ �� �ֽ��ϴ�.

class Scene
{
	friend class Framework;
public:
	//��� ������Ʈ�� ���� Ȥ�� ���ҽ��� �ε�� Initialize���� �̷�������մϴ�.
	//�����ڿ����� ������Ʈ�� ���� Ȥ�� �ε带 ��õ�帮�� �ʽ��ϴ�. (������ �߻��� �� �ֽ��ϴ�.)
	Scene();
	virtual ~Scene();
	
private:
	static Scene* currentScene;
	static Scene* nextScene;
	static void SwapScene();

public:
	static void ChangeScene(Scene* nextScene);		//ChangeScene�� ȣ���Ͽ� Scene�� ȣ���� �� �ֽ��ϴ�.
	static Scene& GetCurrentScene();				//GetCurrentScene�� ȣ���Ͽ� ������ Scene�� ȣ���� �� �ֽ��ϴ�.

private:
	std::list<GameObject*> gameObjectList;			//��� ���ӿ�����Ʈ ����Ʈ
	std::list<GameObject*> renderableList;			//�׸��� �׷���(����) ������Ʈ�� ����Ʈ
	std::list<GameObject*> destroyedObjectList;		//����ó���� ������Ʈ ����Ʈ
	ResourceManager* resourceManager;				//�̹��� ������ ������ ��ü

public:
	//��� ������Ʈ�� ���� Ȥ�� ���ҽ��� �ε�� Initialize���� �̷�������մϴ�.
	//�����ڿ����� ������Ʈ�� ���� Ȥ�� �ε带 ��õ�帮�� �ʽ��ϴ�. (������ �߻��� �� �ֽ��ϴ�.)
	virtual void Initialize() = 0;	//�ʱ�ȭ	(���� ���� �Լ�),
	void Update();					//������Ʈ
	void Render();					//����

public:
	GameObject* PushBackGameObject(GameObject* gameObject);	//���ӿ�����Ʈ Ǫ����
	void Destroy(GameObject* o);							//����ó��

public:
	ResourceManager& GetResourceManager();					//Getter
};

