#include "itkVectorImage.h"
#include "itkHDF5ImageIO.h"
#include "itkImageFileWriter.h"

using namespace std;

typedef float PixelType;

int main (int argc, char* argv[])
{
    // Parse command line
    if (argc != 5) {
        cerr << "Usage: " << argv[0] << " NZ NY NX NC" << endl
             << "where NZ, NY, NX are the 3D-image dimensions," << endl
             << "and NC is the image number of component per pixel." << endl;
        return EXIT_FAILURE;
    }
    const unsigned int nz = atoi( argv[1] );
    const unsigned int ny = atoi( argv[2] );
    const unsigned int nx = atoi( argv[3] );
    const unsigned int nc = atoi( argv[4] );

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
            variableLengthVector[ic] = iz*1000 + iy*100 + ix*10 + ic;
        }
        image->SetPixel(pixelIndex, variableLengthVector);
    }}}

    // Create writer.
    typedef itk::ImageFileWriter<ImageType>  WriterType;
    typedef itk::HDF5ImageIO ImageIOType;
    WriterType::Pointer writer = WriterType::New();

    // Add an observer to record regions written in the HDF5 file.
    ImageIOType::Pointer hdf5IO = ImageIOType::New();
    writer->SetImageIO(hdf5IO);

    // Set output file name.
    ostringstream outputFilename;
    outputFilename << "imtest_z" << nz << "_y" << ny << "_x" << nx << "_c" << nc << ".h5";
    writer->SetFileName(outputFilename.str());

    // Update all the pipeflow.
    writer->SetInput( image );
    writer->Update();

    // Report informations from HDF5 driver.
    cout << outputFilename.str() << endl;

    return EXIT_SUCCESS;
}
