#include "stdafx.h"
#include "Renderer.h"

Renderer::Renderer()
	: Component(), currentSprite(nullptr), alpha(1.0f), initialized(false)
{
}

Renderer::Renderer(Sprite* startSprite, float alpha)
	: Component(), currentSprite(startSprite), alpha(alpha), initialized(true)
{
	D2D1_SIZE_U size = startSprite->bitmap->GetPixelSize();
	width = size.width;
	height = size.height;
	layer = 2;
}

bool Renderer::GetInitialized()
{
	return initialized;
}

Sprite& Renderer::GetSprite()
{
	return *currentSprite;
}

int Renderer::GetWidth()
{
	return width;
}

int Renderer::GetHeight()
{
	return height;
}

float Renderer::GetAlpha()
{
	return alpha;
}

void Renderer::SetAlpha(float a)
{
	alpha = a;
}

int Renderer::GetLayer()
{
	return layer;
}

void Renderer::SetLayer(int l)
{
	layer = l;
}

void Renderer::Render(ID2D1HwndRenderTarget& renderTarget, Transform& transform)
{
	if (!currentSprite||!currentSprite->bitmap)
	{
		return;
	}
	D2D1_SIZE_U size;
	size = currentSprite->bitmap->GetPixelSize();
	
	Point positioningCenter;
	positioningCenter.x = transform.position.x - transform.positioningCenter.x;
	positioningCenter.y = transform.position.y - transform.positioningCenter.y;

	D2D1_RECT_F rect;
	rect.left = positioningCenter.x - size.width * 0.5f;
	rect.top = positioningCenter.y - size.height * 0.5f;
	rect.right = positioningCenter.x + size.width * 0.5f;
	rect.bottom = positioningCenter.y + size.height * 0.5f;

	Point scalingCenter;
	scalingCenter.x = positioningCenter.x + transform.scalingCenter.x;
	scalingCenter.y = positioningCenter.y + transform.scalingCenter.y;

	Point rotatingCenter;
	rotatingCenter.x = positioningCenter.x + transform.rotatingCenter.x;
	rotatingCenter.y = positioningCenter.y + transform.rotatingCenter.y;

	renderTarget.SetTransform(
		D2D1::Matrix3x2F::Scale(
			transform.scale.x,
			transform.scale.y,
			scalingCenter) 
		* D2D1::Matrix3x2F::Rotation(
			transform.rotatingAngle,
			rotatingCenter
		));
	renderTarget.DrawBitmap(currentSprite->bitmap, &rect, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, NULL);

}
