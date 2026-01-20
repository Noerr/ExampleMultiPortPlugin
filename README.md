# Example Multi-Port Reader Plugin

This plugin demonstrates **vtkFileSeriesReader with multiple output ports**, specifically testing [MR !7637](https://gitlab.kitware.com/paraview/paraview/-/merge_requests/7637) which adds auto-detection of output port count.

## What it does

The reader produces **two output ports**:
- **Port 0 (Square)**: A 20x20 square mesh with scalar field `f(t,x,y) = sin(2π(x+y+t))`
- **Port 1 (Circle)**: A circular mesh with scalar field `f(t,x,y) = cos(2π(r+t))`

## File format

`.exmp` files contain a single floating-point time value:
```
0.125
```

## Building

```bash
mkdir build && cd build
cmake -DParaView_DIR=/path/to/paraview/build/lib/cmake/paraview-6.0 ..
make -j4
```

## Testing

1. Generate test data (20 frames, dt=0.125):
   ```bash
   ./generate_test_data.sh /tmp/test_data
   ```

2. Load the plugin in ParaView

3. Open the `.exmp` files (select multiple for time series)

4. Verify:
   - Reader has 2 output ports (Square, Circle)
   - Time slider works across all 20 frames
   - Both meshes animate with time

## MR !7637 Verification

**Without MR !7637**, `vtkFileSeriesReader` hardcodes `SetNumberOfOutputPorts(1)` in its constructor, causing:
- Only one output port visible
- Potential crashes when accessing port 1

**With MR !7637**, `SetReader()` auto-detects the internal reader's output port count (2) and configures the file series reader accordingly.

### Verified Results (2025-01-20)

```
Reader: vtkFileSeriesReader
Output ports: 2
Time steps: [0.0, 0.125, 0.25, ..., 2.375] (20 frames)

Port 0: 400 points, 361 cells, arrays: ['SquareWave']
Port 1: 1801 points, 1800 cells, arrays: ['CircleWave']

Time stepping test:
t=0.0: SquareWave[0]=0.0000, CircleWave[0]=1.0000
t=0.5: SquareWave[0]=-0.0000, CircleWave[0]=-1.0000
t=1.0: SquareWave[0]=0.0000, CircleWave[0]=1.0000
```

Both output ports correctly:
- Have distinct geometry (square vs circle mesh)
- Have distinct scalar arrays (SquareWave vs CircleWave)
- Update with time series navigation
