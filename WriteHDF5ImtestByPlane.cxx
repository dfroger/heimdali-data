#include "itkVectorImage.h"
#include "itkHDF5ImageIO.h"
#include "itkImageFileWriter.h"

using namespace std;

typedef float PixelType;

unsigned int ZD=2, YD=1, XD=0;

int main (int argc, char* argv[])
{
    const unsigned int nz = 5;
    const unsigned int ny = 4;
    const unsigned int nx = 3;
    const unsigned int nc = 2;

    // Allocate image.
    const int Dimension = 3;
    typedef itk::VectorImage<PixelType, Dimension> ImageType;
    ImageType::IndexType start;
    start.Fill(0);
    ImageType::SizeType size;
    size[ZD] = 1;
    size[YD] = ny;
    size[XD] = nx;
    ImageType::RegionType region(start,size);
    ImageType::Pointer image = ImageType::New();
    image->SetRegions(region);
    image->SetVectorLength(nc);
    image->Allocate();

    // Pixel value
    ImageType::IndexType pixelIndex;
    typedef itk::VariableLengthVector<double> VariableVectorType;
    VariableVectorType value;
    value.SetSize(nc);

    // Writer
    typedef itk::ImageFileWriter<ImageType>  WriterType;
    WriterType::Pointer writer;

    for (int iz=0 ; iz < nz ; ++iz) { 
        // Set image pixel values.
        pixelIndex[ZD] = 0;
        for (int iy=0 ; iy < ny ; ++iy) {
            pixelIndex[YD] = iy;
            for (int ix=0 ; ix < nx ; ++ix) {
                pixelIndex[XD] = ix;
                for (int ic=0 ; ic < nc ; ++ic) {
                    value[ic] = iz*1000 + iy*100 + ix*10 + ic;
                }
                image->SetPixel(pixelIndex, value);
            }
        }

        // Set output file name.
        ostringstream outputFilename;
        outputFilename << "imtest_iz"<< iz << "_z5_y4_x3_c2.h5";

        // Write image
        writer = WriterType::New();
        writer->SetFileName(outputFilename.str());
        writer->SetInput( image );
        writer->Update();

        cout << outputFilename.str() << endl;
    }

    return EXIT_SUCCESS;
}
