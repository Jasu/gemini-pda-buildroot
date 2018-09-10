# SMI (Smart Multimedia Interface) / LARB ports

See `drivers/misc/mediatek/m4u/mt6797/m4u_platform.h`.

## LARB 0 (Display / Multimedia Data Path)

| Port | Description                      |
| ---- | -------------------------------- |
|    0 | Display overlay 0                |
|    1 | Display 2-layer overlay 0 LARB 0 |
|    2 | Display RDMA 0                   |
|    3 | Display WDMA 0                   |
|    4 | MDP RDMA 0                       |
|    5 | MDP WDMA 0                       |
|    6 | MDP Rotation 0                   |
|    7 | Display fake 0                   |

## LARB 1 (Video decoding)

Identical to LARB 1 on the MT8173.

| Port | Description  |
| ---- | ------------ |
|    0 | VDEC MC      |
|    1 | VDEC PP      |
|    2 | VDEC UFO     |
|    3 | VDEC VLD     |
|    4 | VDEC VLD 2   |
|    5 | VDEC AVC MV  |
|    6 | VDEC PRED RD |
|    7 | VDEC PRED WR |
|    8 | VDEC PPWRAP  |
|    9 | VDEC TILE    |

## LARB 2 (Camera)

| Port | Description |
| ---- | ----------- |
|    0 | IMGO        |
|    1 | RRZ 0       |
|    2 | AAO         |
|    3 | AFO         |
|    4 | LSCI 0      |
|    5 | LSCI 1      |
|    6 | SV 0        |
|    7 | SV 1        |
|    8 | SV 2        |
|    9 | LCSO        |
|   10 | UFEO        |
|   11 | BPCI        |
|   12 | PDO         |
|   13 | RAWI        |

## LARB 3 (Video encoding and JPEG decoding/encoding)

Identical to LARB 3 on the MT8173.

| Port | Description     |
| ---- | --------------- |
|    0 | VENC RCPU       |
|    1 | VENC REC        |
|    2 | VENC BSDMA      |
|    3 | VENC SV COMV    |
|    4 | VENC RD COMV    |
|    5 | JPEG ENC RDMA   |
|    6 | JPEG ENC BSDMA  |
|    7 | JPEG DEC WDMA   |
|    8 | JPEG DEC BSDMA  |
|    9 | VENC CUR LUMA   |
|   10 | VENC CUR CHROMA |
|   11 | VENC REF LUMA   |
|   12 | VENC REF CHROMA |
|   13 | VENC NBM RDMA   |
|   14 | VENC NBM WDMA   |

## LARB 4 (MJC)

| Port | Description |
| ---- | ----------- |
|    0 | MV RD       |
|    1 | MV WR       |
|    2 | DMA RD      |
|    3 | DMA WR      |

## LARB 5 (Display / Multimedia Data Path)

| Port | Description                      |
| ---- | -------------------------------- |
|    0 | Display overlay 1                |
|    1 | Display overlay 1 2-layer        |
|    2 | Display RDMA 1                   |
|    3 | Display WDMA 1                   |
|    4 | Display overdrive read           |
|    5 | Display overdrive write          |
|    6 | Display overlay 0 2-layer LARB 5 |
|    7 | Multimedia data path RDMA 1      |
|    8 | Multimedia data path rotation 1  |
|    9 | Display fake LARB 5              |

## LARB 6 (Camera / Face detection)

| Port | Description |
| ---- | ----------- |
|    0 | IMGI        |
|    1 | IMG2O       |
|    2 | IMG3O       |
|    3 | VIPI        |
|    4 | ICEI        |
|    5 | RP          |
|    6 | WR          |
|    7 | RB          |
|    8 | DPE RDMA    |
|    9 | DPE WDMA    |
