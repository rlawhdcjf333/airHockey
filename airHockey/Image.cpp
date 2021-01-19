#include "pch.h"
#include "Image.h"

Image::Image()
	:mImageBuffer(NULL), mIsTrans(0)
{}

Image::~Image() {
	ReleaseBuffer();
}

void Image::ReleaseBuffer() {
	if (mImageBuffer != NULL) {
		SelectObject(mImageBuffer->hdc, mImageBuffer->oldBitm);
		DeleteObject(mImageBuffer->bitm);

		delete mImageBuffer;
		mImageBuffer = NULL;
	}
}

bool Image::CreateEmpty(int w, int h) {

	if (mImageBuffer != NULL) {

		ReleaseBuffer();
	}

	HDC hdc = GetDC(g_hWnd);

	mImageBuffer = new ImageBuffer();
	mImageBuffer->loadt = LoadType::Empty;
	mImageBuffer->registerID = 0;
	mImageBuffer->hdc = CreateCompatibleDC(hdc);
	mImageBuffer->bitm = (HBITMAP)CreateCompatibleBitmap(hdc, w, h);
	mImageBuffer->oldBitm = (HBITMAP)SelectObject(mImageBuffer->hdc, mImageBuffer->bitm);
	mImageBuffer->w = w;
	mImageBuffer->h = h;

	ReleaseDC(g_hWnd, hdc);

	if (mImageBuffer->bitm == NULL) {
		ReleaseBuffer();
		return false;
	}

	return false;
}

bool Image::LoadFromFile(wstring fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	if (fileName.length() <= 0) {

		return false;
	}

	if (mImageBuffer != NULL) {

		ReleaseBuffer();
	}

	HDC hdc = GetDC(g_hWnd);

	mImageBuffer = new ImageBuffer();
	mImageBuffer->loadt = LoadType::File;
	mImageBuffer->registerID = 0;
	mImageBuffer->hdc = CreateCompatibleDC(hdc);
	mImageBuffer->bitm = (HBITMAP)LoadImage(

		g_hInstance,
		fileName.c_str(),
		IMAGE_BITMAP,
		width,
		height,
		LR_LOADFROMFILE
	);

	mImageBuffer->oldBitm = (HBITMAP)SelectObject(mImageBuffer->hdc, mImageBuffer->bitm);
	mImageBuffer->w = width;
	mImageBuffer->h = height;

	mIsTrans = isTrans;
	mTransColor = transColor;

	ReleaseDC(g_hWnd, hdc);

	if (mImageBuffer->bitm == NULL) {

		ReleaseBuffer();
		return false;
	}

	return false;
}

void Image::Render(HDC hdc, int x, int y) {

	if (mIsTrans) {

		GdiTransparentBlt(
			hdc, x, y,
			mImageBuffer->w, mImageBuffer->h,
			mImageBuffer->hdc, 0, 0,
			mImageBuffer->w, mImageBuffer->h,
			mTransColor
		);
	}

	else {
		BitBlt(
			hdc, x, y,
			mImageBuffer->w, mImageBuffer->h,
			mImageBuffer->hdc, 0, 0, SRCCOPY);
	}
}