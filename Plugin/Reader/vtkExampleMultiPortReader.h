#ifndef vtkExampleMultiPortReader_h
#define vtkExampleMultiPortReader_h

#include "ExampleMultiPortReaderCoreModule.h" // For export macro
#include "vtkMultiBlockDataSetAlgorithm.h"

#include <string>

/**
 * @class vtkExampleMultiPortReader
 * @brief Example reader with 2 output ports to demonstrate vtkFileSeriesReader
 *
 * This reader demonstrates multi-output-port support with vtkFileSeriesReader.
 * It reads simple .ex_multiport files containing a single time value, and
 * generates two meshes:
 *   - Port 0: Square mesh with f(t,x,y) = sin(2*pi*(x + y + t))
 *   - Port 1: Circle mesh with f(t,x,y) = cos(2*pi*(r + t)) where r = sqrt(x^2+y^2)
 *
 * File format: Single line containing a floating-point time value.
 */
class EXAMPLEMULTIPORTREADERCORE_EXPORT vtkExampleMultiPortReader
  : public vtkMultiBlockDataSetAlgorithm
{
public:
  static vtkExampleMultiPortReader* New();
  vtkTypeMacro(vtkExampleMultiPortReader, vtkMultiBlockDataSetAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  ///@{
  /**
   * Specify the file name.
   */
  vtkSetStringMacro(FileName);
  vtkGetStringMacro(FileName);
  ///@}

  /**
   * Test whether the file can be read.
   */
  int CanReadFile(const char* filename);

protected:
  vtkExampleMultiPortReader();
  ~vtkExampleMultiPortReader() override;

  int FillOutputPortInformation(int port, vtkInformation* info) override;
  int RequestInformation(vtkInformation*, vtkInformationVector**, vtkInformationVector*) override;
  int RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector*) override;

private:
  vtkExampleMultiPortReader(const vtkExampleMultiPortReader&) = delete;
  void operator=(const vtkExampleMultiPortReader&) = delete;

  char* FileName;

  // Read the time value from file
  bool ReadTimeValue(const char* filename, double& time);

  // Generate the square mesh for port 0
  vtkSmartPointer<vtkDataObject> GenerateSquareMesh(double time);

  // Generate the circle mesh for port 1
  vtkSmartPointer<vtkDataObject> GenerateCircleMesh(double time);
};

#endif
