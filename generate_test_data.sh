#!/bin/bash
# Generate test .exmp files with time values

OUTDIR="${1:-.}"

mkdir -p "$OUTDIR"

# Generate 20 time steps with dt=0.125
for i in $(seq 0 19); do
  TIME=$(echo "scale=6; $i * 0.125" | bc)
  FILE="$OUTDIR/data_$(printf '%04d' $i).exmp"
  echo "$TIME" > "$FILE"
  echo "Created $FILE with time = $TIME"
done

echo ""
echo "Test files created in $OUTDIR"
echo "To test: select all .exmp files in ParaView's Open dialog"
