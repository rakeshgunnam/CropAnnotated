#include <iostream>
#include <fstream>
#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;



void CropAndSaveImg(string str, string imgPath, string savePath, int count, string NPrefix)
{
	// Used to split string around spaces.

	Mat OImag, CropImg;

	OImag = imread(imgPath);
	istringstream ss(str);

	string word; // for storing each word

	// Traverse through all words
	// while loop till we get 
	// strings to store in string word
	int itr = 0;
	string pnt[50];
	while (ss >> word)
	{
		// print the read word
		pnt[itr] = word;
		//cout << word << "\n";
		++itr;
	}

	int ClassId = stoi(pnt[0]);
	float C_X = stof(pnt[1]);
	float C_Y = stof(pnt[2]);
	float C_Width = stof(pnt[3]);
	float C_Height = stof(pnt[4]);

	int x = (int)((C_X * OImag.size().width) - (C_Width*(OImag.size().width/2)));
	int y = (int)((C_Y * OImag.size().height) - (C_Height * (OImag.size().height/2)));
	int CropWidth = C_Width * OImag.cols;
	int CropHeight = C_Height * OImag.rows;

	Rect ROI(x, y, CropWidth, CropHeight);

	CropImg = OImag(ROI);

	imwrite(savePath+"\\"+NPrefix+to_string(count)+".jpg", CropImg);

	cout << x << endl << y << endl << CropWidth << endl << CropHeight << endl << ClassId << endl;

}


int main() {

	cout << "Enter Root Path: " << endl;
	string root;
	cin >> root;
	
	cout << endl << "Enter Destination Path: " << endl;
	string DestPath;
	cin >> DestPath;

	cout << endl << "Enter Name Prefix: " << endl;
	string NPrefix;
	cin >> NPrefix;

	vector<string> imgs;
	vector<string> Txts;
	glob(root + "\\*.jpg", imgs, false);
	glob(root + "\\*.txt", Txts, false);

	/*Mat img = imread(imgs[0]);
	imshow("Image", img);*/
	//waitKey(0);
	int count = 0;
	fstream TxtFile;
	for (int i = 0; i < imgs.size(); i++)
	{
		
		for (int j = 0; j < Txts.size();j++)
		{
			
			if (imgs[i].substr(0, imgs[i].length() - 4) == Txts[j].substr(0, Txts[j].length() - 4))
			{
				
				TxtFile.open(Txts[j], ios::in);
				string line;

				while (getline(TxtFile, line))
				{
					
					CropAndSaveImg(line,imgs[i],DestPath,count,NPrefix);
					++count;
				}
				
				TxtFile.close();

				cout << endl << endl;
				
			}
		}
		
	}
	

	cout << endl << count << endl;
	
	return 0;
}


