# ExampleMultiPortPlugin

Test plugin for [ParaView MR !7637](https://gitlab.kitware.com/paraview/paraview/-/merge_requests/7637) - auto-detection of output port count in vtkFileSeriesReader.

## Build Commands

```bash
mkdir build && cd build
cmake -DParaView_DIR=/path/to/paraview/build/lib/cmake/paraview-6.0 ..
make -j4
```

## Test Commands

```bash
# Generate 20 test frames
./generate_test_data.sh /tmp/test_data

# Verify with pvpython
pvpython << 'EOF'
import paraview.simple as pv
pv.LoadPlugin('build/lib/ExampleMultiPortReader/ExampleMultiPortReader.so')
files = [f'/tmp/test_data/data_{i:04d}.exmp' for i in range(20)]
reader = pv.ExampleMultiPortReader(FileName=files)
reader.UpdatePipeline()
vtk_obj = reader.GetClientSideObject()
print(f"Output ports: {vtk_obj.GetNumberOfOutputPorts()}")
for port in range(2):
    out = vtk_obj.GetOutputDataObject(port)
    print(f"Port {port}: {out.GetNumberOfPoints()} points")
EOF
```

## Expected Output

```
Output ports: 2
Port 0: 400 points
Port 1: 1801 points
```

## File Structure

```
ExampleMultiPortPlugin/
├── CMakeLists.txt
├── Plugin/
│   ├── paraview.plugin
│   ├── CMakeLists.txt
│   └── Reader/
│       ├── vtk.module
│       ├── CMakeLists.txt
│       ├── vtkExampleMultiPortReader.h
│       ├── vtkExampleMultiPortReader.cxx
│       └── ExampleMultiPortReader.xml
├── generate_test_data.sh
└── README.md
```
