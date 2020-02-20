#include <wx/bitmap.h>
#include <wx/image.h>
#include <vector>

class{
	
	public wxImage uploadImage(wxString imageName)
	{
		wxImage uploadedImage;
	
		while (!uploadedImage.IsOk())
		{
//			uploadedImage.LoadFile	( 	const wxString & name, 
//										const wxString & mimetype,
//										int  index = -1 
//									);
		}
		
		return uploadedImage
	}
	
	private std::vector< vector< vector< unsigned char > > > retrieveColor(wxImage image)
	{
		int width, height;
		unsigned char red, green, blue;
		
		width = image.GetWidth();
		height = image.GetHeight();
		std::vector< vector< vector< unsigned char > > > retrievedColor;
		
		for (int y = 0; y < height; y++)
		{
			retrieveColor.pushback();
			
			for (int x = 0; x < width; x++)
			{
				red = image.GetRed();
				green = image.GetGreen();
				blue = (image.GetBlue();
				retrieveColor[y].push_back({red, green, blue});
			}
		}
	}
	
	private std::vector< vector<unsigned char> > convertColortoLuminance
										(vector< vector< vector < unsigned char > > > color)
	{
		std::vector< vector<unsigned char> > luminance;
		
//		float FxaaLuma(float3 rgb) {
//			return rgb.y * (0.587/0.299) + rgb.x; 
//		}


	}
};

