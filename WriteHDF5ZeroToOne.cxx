#include "itkVectorImage.h"
#include "itkHDF5ImageIO.h"
#include "itkImageFileWriter.h"

using namespace std;

typedef float PixelType;

int main (int argc, char* argv[])
{
    // Parse command line
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
    size[2] = nz;
    size[1] = ny;
    size[0] = nx;
    ImageType::RegionType region(start,size);
    ImageType::Pointer image = ImageType::New();
    image->SetRegions(region);
    image->SetVectorLength(nc);
    image->Allocate();

    // Set image pixel values.
    ImageType::IndexType pixelIndex;
    typedef itk::VariableLengthVector<double> VariableVectorType;
    VariableVectorType variableLengthVector;
    variableLengthVector.SetSize(nc);
    for (int iz=0 ; iz < nz ; ++iz) { pixelIndex[2] = iz;
    for (int iy=0 ; iy < ny ; ++iy) { pixelIndex[1] = iy;
    for (int ix=0 ; ix < nx ; ++ix) { pixelIndex[0] = ix;
        for (int ic=0 ; ic < nc ; ++ic) {
            // Value are defined between 0 and 1 and are uniq
            variableLengthVector[ic] = iz*0.211 + iy*0.047 + ix*0.007 + 0.001*ic;
        }
        image->SetPixel(pixelIndex, variableLengthVector);
    }}}

    // Create writer.
    typedef itk::ImageFileWriter<ImageType>  WriterType;
    typedef itk::HDF5ImageIO ImageIOType;
    WriterType::Pointer writer = WriterType::New();
    writer->SetFileName("zero_to_one_r5.h5");
    writer->SetInput( image );
    writer->Update();

    return EXIT_SUCCESS;
}
