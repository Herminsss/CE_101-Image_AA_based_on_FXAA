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
	
//---------------------------------------------------------------------
	
	private std::vector< vector< vector< double > > > 
							retrieveImageColor (wxImage image)
	{
		int width, height;
		double red, green, blue, luma;
		std::vector< vector< vector< unsigned char > > > color;
		
		height = image.GetHeight();
		width = image.GetWidth();
		
		for (int y = 0; y < height; y++)
		{
			retrieveColor.pushback();
			
			for (int x = 0; x < width; x++)
			{
				red = image.GetRed(x, y) / 255;
				green = image.GetGreen(x, y) / 255;
				blue = image.GetBlue(x, y) / 255;
				luma = colorToLuma(red, green, blue)
				
				color[y].push_back({red, green, blue, luma});
			}
		}
		
		return color;
	}
	
//	private std::vector< vector< unsigned char > > convertColortoLuminance
//										(std::vector< vector< vector < unsigned char > > > color)
//	{
//		std::vector< vector<unsigned char> > luminance;
//		unsigned char currLuminance;
//		
//		height = color.size();
//		width = color[0].size();
//		
//		for (int y = 0; y < height; y++)
//		{
//			luminance.pushback();
//			
//			for (int x = 0; x < width; x++)
//			{
//				currLuminance = color[y][x][0]*0.2126 + color[y][x][1]*0.7152 + color[y][x][2]*0.0722;
//				luminance.pushback[y]](currLuminance);
//			}
//		}
//	}
	
	private unsigned char colorToLuma	(	double red, 
											double green, 
											double blue
										)
	{
		double luma;
		luma = red*0.2126 + green*0.7152 + blue*0.0722;
		return luma;
	}
	
	
	private std::vector< vector< bool > > detectEdge 
		(	std::vector< vector< vector< unsigned char > > > color,
			float edgeThreshold, 
			float edgeThresholdMin
		)
	{
		std::vector< vector< bool > > edgeDetected;
		height = color.size();
		width = color[0].size();
		double luma[5]
		double rangeMin, rangeMax, range;
		
		for (int y = 1; y < height-1; y++)
		{
			edgeDetected.pushback();
			
			for (int x = 1; x < width-1; x++)
			{
				luma[0] = color[y-1][x][3]; //Top Pixel
				luma[1] = color[y][x-1][3]; //left Pixel
				luma[2] = color[y][x][3]; //Current Pixel
				luma[3] = color[y][x+1][3]; //Right Pixel
				luma[4] = color[y+1][x][3]; //Bottom Pixel
				
				rangeMin = luma[0];
				rangeMax = luma[0];
				
				for (int i = 1; i < 5; i++)
				{
					rangeMin = luma[i] < rangeMin ? luma[i] : rangeMin;
					rangeMax = luma[i] > rangeMax ? luma[i] : rangeMax;
				}
				
				range = rangeMax - rangeMin;				
				
//				float rangeMin = min(lumaM, min(min(lumaN, lumaW), min(lumaS, lumaE)));
//				float rangeMax = max(lumaM, max(max(lumaN, lumaW), max(lumaS, lumaE)));
//				float range = rangeMax -rangeMin;
//				if(range < max(FXAA_EDGE_THRESHOLD_MIN, rangeMax * XAA_EDGE_THRESHOLD)) return FxaaFilterReturn(rgbM);
				
				if (range < edgeThresholdMin || range < edgeThreshold * rangeMax)
				{
					edgeDetected[y].pushback(false);
				}
				else
				{
					edgeDetected[y].pushback(true);
				}
			}
		}
		
		return edgeDetected;
	} 
	
	private wxImage antiAliasImage 	(	wxImage inputImage, 
										float edgeThresholdMin, 
										float edgeThreshold
									)
	{
		std::vector< vector< vector< double > > > color = retrieveImageColor (inputImage);
		std::vector< vector< bool > > edges = (color, edgeThreshold, edgeThresholdMin);
	}
};

