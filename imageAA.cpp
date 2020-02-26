#include <wx/bitmap.h>
#include <wx/image.h>
#include <vector>

class imageAA{
	
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
		std::vector< vector< vector< unsigned char > > > retrievedColor;
		
		height = image.GetHeight();
		width = image.GetWidth();
		
		for (int y = 0; y < height; y++)
		{
			retrieveColor.pushback();
			
			for (int x = 0; x < width; x++)
			{
				red = image.GetRed(x, y);
				green = image.GetGreen(x, y);
				blue = (image.GetBlue(x, y);
				retrieveColor[y].push_back({red, green, blue});
			}
		}
	}
	
	private std::vector< vector< unsigned char > > convertColortoLuminance
										(std::vector< vector< vector < unsigned char > > > color)
	{
		std::vector< vector<unsigned char> > luminance;
		unsigned char currLuminance;
		
		height = color.size();
		width = color[0].size();
		
		for (int y = 0; y < height; y++)
		{
			luminance.pushback();
			
			for (int x = 0; x < width; x++)
			{
				currLuminance = color[y][x][0]*0.2126 + color[y][x][1]*0.7152 + color[y][x][2]*0.0722;
				luminance.pushback[y]](currLuminance);
			}
		}
	}
	
//	private unsigned char sConvertColortoLuminance(std::vector< unsigned char > color)
//	{
//		unsigned char luminance;
//		luminance = color[0]*0.2126 + color[1]*0.7152 + color[2]*0.0722;
//	}
	
	private std::vector< vector< bool > > detectEdge (std::vector< vector< unsigned char > > luminance, 
														float edge_threshold, float edge_threshold_min)
	{
		std::vector< vector< bool > > edgeDetected;
		height = luminance.size();
		width = luminance[0].size();
		unsigned char lumaN, lumaW, lumaE, lumaS;
		
		for (int y = 1; y < height-1; y++)
		{
			edgeDetected.pushback();
			
			for (int x = 1; x < width-1; x++)
			{
				lumaN = luminance[y-1][x];
				lumaW = luminance[y][x-1];
				lumaE = luminance[y][x+1];
				lumaS = luminance[y+1][x];
				
				
				
				if ()
				{
					edgeDetected.pushback(true);
				}
				else
				{
					edgeDetected.pushback(false);
				}
			}
		}
	} 
};

