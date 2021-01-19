#pragma once

//double buffering
class Image
{
	enum LoadType : int {

		Resource = 0,
		File,
		Empty,
		End
	};
	struct ImageBuffer {

		ULONG registerID;
		HDC hdc;
		HBITMAP bitm;
		HBITMAP oldBitm;
		int w;
		int h;
		LoadType loadt;

	};
private:
	ImageBuffer* mImageBuffer;
	wstring mFileName;
	bool mIsTrans;
	COLORREF mTransColor;

public:
	Image();
	~Image();

	void ReleaseBuffer();

	bool CreateEmpty(int w, int h);
	bool LoadFromFile(wstring fileName, int width, int height, bool isTrans, COLORREF transColor);

	void Render(HDC h, int x, int y);

	HDC GetHDC() { return mImageBuffer->hdc; }
};

