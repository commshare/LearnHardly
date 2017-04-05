// Describes an image
// https://github.com/openhumanoids/openni2-camera-lcm/blob/master/lcmtypes/openni2_image_t.lcm
// This type should be kept compatible with camlcm.image_t, as defined
// in camunits-extra

struct image_t
{
    // microseconds since the epoch
    int64_t  utime;

    int32_t  width;
    int32_t  height;
    int32_t  row_stride;

    int32_t  pixelformat;

    int32_t  size;
    byte     data[size];

    // metadata dictionary
    int32_t nmetadata;
    image_metadata_t metadata[nmetadata];

    // these values are to be kept in sync with the CamPixelFormat enumeration
    // in the Camunits library.  See camunits/pixels.h in Camunits
    const int32_t PIXEL_FORMAT_UYVY             = 1498831189;
    const int32_t PIXEL_FORMAT_YUYV             = 1448695129;
    const int32_t PIXEL_FORMAT_IYU1             = 827677001;
    const int32_t PIXEL_FORMAT_IYU2             = 844454217;
    const int32_t PIXEL_FORMAT_YUV420           = 842093913;
    const int32_t PIXEL_FORMAT_YUV411P          = 1345401140;
    const int32_t PIXEL_FORMAT_I420             = 808596553;
    const int32_t PIXEL_FORMAT_NV12             = 842094158;
    const int32_t PIXEL_FORMAT_GRAY             = 1497715271;
    const int32_t PIXEL_FORMAT_RGB              = 859981650;
    const int32_t PIXEL_FORMAT_BGR              = 861030210;
    const int32_t PIXEL_FORMAT_RGBA             = 876758866;
    const int32_t PIXEL_FORMAT_BGRA             = 877807426;
    const int32_t PIXEL_FORMAT_BAYER_BGGR       = 825770306;
    const int32_t PIXEL_FORMAT_BAYER_GBRG       = 844650584;
    const int32_t PIXEL_FORMAT_BAYER_GRBG       = 861427800;
    const int32_t PIXEL_FORMAT_BAYER_RGGB       = 878205016;
    const int32_t PIXEL_FORMAT_BE_BAYER16_BGGR  = 826360386;
    const int32_t PIXEL_FORMAT_BE_BAYER16_GBRG  = 843137602;
    const int32_t PIXEL_FORMAT_BE_BAYER16_GRBG  = 859914818;
    const int32_t PIXEL_FORMAT_BE_BAYER16_RGGB  = 876692034;
    const int32_t PIXEL_FORMAT_LE_BAYER16_BGGR  = 826360396;
    const int32_t PIXEL_FORMAT_LE_BAYER16_GBRG  = 843137612;
    const int32_t PIXEL_FORMAT_LE_BAYER16_GRBG  = 859914828;
    const int32_t PIXEL_FORMAT_LE_BAYER16_RGGB  = 876692044;
    const int32_t PIXEL_FORMAT_MJPEG            = 1196444237;
    const int32_t PIXEL_FORMAT_BE_GRAY16        = 357;
    const int32_t PIXEL_FORMAT_LE_GRAY16        = 909199180;
    const int32_t PIXEL_FORMAT_BE_RGB16         = 358;
    const int32_t PIXEL_FORMAT_LE_RGB16         = 1279412050;
    const int32_t PIXEL_FORMAT_BE_SIGNED_GRAY16 = 359;
    const int32_t PIXEL_FORMAT_BE_SIGNED_RGB16  = 360;
    const int32_t PIXEL_FORMAT_FLOAT_GRAY32     = 842221382;
    const int32_t PIXEL_FORMAT_INVALID          = -2;
    const int32_t PIXEL_FORMAT_ANY              = -1;



    ##2 
[https://github.com/aramg/droidcam/blob/master/linux/fourcc.out]

 V4L2_PIX_FMT_RGB332 = 826427218
 V4L2_PIX_FMT_RGB444 = 875836498
 V4L2_PIX_FMT_RGB555 = 1329743698
 V4L2_PIX_FMT_RGB565 = 1346520914
 V4L2_PIX_FMT_RGB555X= 1363298130
 V4L2_PIX_FMT_RGB565X= 1380075346
 V4L2_PIX_FMT_BGR24  = 861030210
 V4L2_PIX_FMT_RGB24  = 859981650
 V4L2_PIX_FMT_BGR32  = 877807426
 V4L2_PIX_FMT_RGB32  = 876758866
 V4L2_PIX_FMT_GREY  = 1497715271
 V4L2_PIX_FMT_Y16   = 540422489
 V4L2_PIX_FMT_PAL8  = 944521552
 V4L2_PIX_FMT_YVU410 = 961893977
 V4L2_PIX_FMT_YVU420 = 842094169
 V4L2_PIX_FMT_YUYV   = 1448695129
 V4L2_PIX_FMT_YYUV   = 1448434009
 V4L2_PIX_FMT_YVYU   = 1431918169
 V4L2_PIX_FMT_UYVY   = 1498831189
 V4L2_PIX_FMT_VYUY   = 1498765654
 V4L2_PIX_FMT_YUV422P= 1345466932
 V4L2_PIX_FMT_YUV411P= 1345401140
 V4L2_PIX_FMT_Y41P   = 1345401945
 V4L2_PIX_FMT_YUV444 = 875836505
 V4L2_PIX_FMT_YUV555 = 1331058009
 V4L2_PIX_FMT_YUV565 = 1347835225   /*有见到,是VLC的VLC_CODEC_YUVP*/
 V4L2_PIX_FMT_YUV32  = 878073177
 V4L2_PIX_FMT_YUV410 = 961959257
 V4L2_PIX_FMT_YUV420 = 842093913
 V4L2_PIX_FMT_HI240  = 875710792
 V4L2_PIX_FMT_HM12   = 842091848
 V4L2_PIX_FMT_NV12   = 842094158
 V4L2_PIX_FMT_NV21   = 825382478
 V4L2_PIX_FMT_NV16   = 909203022
 V4L2_PIX_FMT_NV61   = 825644622
 V4L2_PIX_FMT_SBGGR8 = 825770306
 V4L2_PIX_FMT_SGBRG8 = 1196573255
 V4L2_PIX_FMT_SGRBG8 = 1195528775
 V4L2_PIX_FMT_SGRBG10= 808534338
 V4L2_PIX_FMT_SGRBG10DPCM8= 808535106
 V4L2_PIX_FMT_SBGGR16 = 844257602
 V4L2_PIX_FMT_MJPEG  = 1196444237
 V4L2_PIX_FMT_JPEG   = 1195724874
 V4L2_PIX_FMT_DV     = 1685288548
 V4L2_PIX_FMT_MPEG   = 1195724877
V4L2_PIX_FMT_WNVA         = 1096175191
V4L2_PIX_FMT_SN9C10X      = 808532307
V4L2_PIX_FMT_SN9C20X_I420 = 808597843
V4L2_PIX_FMT_PWC1         = 826496848
V4L2_PIX_FMT_PWC2         = 843274064
V4L2_PIX_FMT_ET61X251     = 892483141
V4L2_PIX_FMT_SPCA501      = 825242963
V4L2_PIX_FMT_SPCA505      = 892351827
V4L2_PIX_FMT_SPCA508      = 942683475
V4L2_PIX_FMT_SPCA561      = 825636179
V4L2_PIX_FMT_PAC207       = 925905488
V4L2_PIX_FMT_MR97310A     = 808530765
V4L2_PIX_FMT_SQ905C       = 1127559225
V4L2_PIX_FMT_PJPG         = 1196444240
V4L2_PIX_FMT_OV511        = 825308495
V4L2_PIX_FMT_OV518        = 942749007



##3
[http://www.ithao123.cn/content-9835478.html
]
   810961203 {3IV0} : result := 'MPEG4-based codec 3ivx';
    827738419 {3IV1} : result := 'MPEG4-based codec 3ivx';
    844515635 {3IV2} : result := 'MPEG4-based codec 3ivx';
   1482049843 {3IVX} : result := 'MPEG4-based codec 3ivx';
   1129529665 {AASC} : result := 'Autodesk Animator codec';
   1381581377 {ABYR} : result := 'Kensington codec';
   1229800769 {AEMI} : result := 'Array VideoONE MPEG1-I Capture';
   1129072193 {AFLC} : result := 'Autodesk Animator FLC (256 color)';
   1229735489 {AFLI} : result := 'Autodesk Animator FLI (256 color)';
   1196444993 {AMPG} : result := 'Array VideoONE MPEG';
   1296649793 {ANIM} : result := 'Intel RDX';
    825512001 {AP41} : result := 'AngelPotion Definitive (hack MS MP43)';
    827740993 {ASV1} : result := 'Asus Video V1';
    844518209 {ASV2} : result := 'Asus Video V2';
   1482052417 {ASVX} : result := 'Asus Video 2.0';
    844256577 {AUR2} : result := 'Aura 2 Codec - YUV 422';
   1095914817 {AURA} : result := 'Aura 1 Codec - YUV 411';
   1245992513 {AVDJ} : result := 'Avid Motion JPEG';
   1314018881 {AVRN} : result := 'Avid Motion JPEG';
   1380997697 {AZPR} : result := 'Quicktime Apple Video';
   1263421762 {BINK} : result := 'Bink Video (RAD Game Tools) (256 color)';
    808604738 {BT20} : result := 'Conexant (ex Brooktree) ProSummer MediaStream';
   1447253058 {BTCV} : result := 'Conexant Composite Video';
   1129731138 {BTVC} : result := 'Conexant Composite Video';
    808539970 {BW10} : result := 'Data Translation Broadway MPEG Capture/Compression';
    842089283 {CC12} : result := 'Intel YUV12 Codec';
   1129727043 {CDVC} : result := 'Canopus DV Codec';
   1128482371 {CFCC} : result := 'Conkrete DPS Perception Motion JPEG';
   1229211459 {CGDI} : result := 'Camcorder Video (MS Office 97)';
   1296123971 {CHAM} : result := 'WinNow Caviara Champagne';
   1196444227 {CJPG} : result := 'Creative Video Blaster Webcam Go JPEG';
   1380600899 {CLJR} : result := 'Cirrus Logic YUV 4:1:1';
   1264143683 {CMYK} : result := 'Common Data Format in Printing';
   1095520323 {CPLA} : result := 'Weitek YUV 4:2:0 Planar';
   1296126531 {CRAM} : result := 'Microsoft Video 1';
   1145656899 {CVID} : result := 'Cinepak by Radius YUV 4:2:2';
   1414289219 {CWLT} : result := 'Microsoft Color WLT DIB';
   1448433987 {CYUV} : result := 'Creative Labs YUV 4:2:2';
   1498765635 {CYUY} : result := 'ATI Technologies YUV';
    825635396 {D261} : result := 'H.261';
    859189828 {D263} : result := 'H.263';
      4344132 {DIB } : result := 'Full Frames (Uncompressed)';
    827738436 {DIV1} : result := 'FFmpeg-4 V1 (hacked MS MPEG-4 V1)';
    844515652 {DIV2} : result := 'FFmpeg-4 V2 (hacked MS MPEG-4 V2)';
    861292868 {DIV3} : result := 'DivX;-) MPEG-4 Low-Motion';
    878070084 {DIV4} : result := 'DivX;-) MPEG-4 Fast-Motion';
    894847300 {DIV5} : result := 'DivX MPEG-4';
    911624516 {DIV6} : result := 'DivX MPEG-4';
   1482049860 {DIVX} : result := 'OpenDivX (DivX 4.0 and later)';
    826428740 {DMB1} : result := 'Matrox Rainbow Runner hardware compression (Motion JPEG)';
    843205956 {DMB2} : result := 'Motion JPEG codec used by Paradigm';
    810766404 {DPS0} : result := 'DPS Reality Motion JPEG';
   1129533508 {DPSC} : result := 'DPS PAR Motion JPEG';
   1146508100 {DSVD} : result := 'Microsoft DirectShow DV';
   1262703940 {DUCK} : result := 'True Motion 1.0';
    892491332 {DV25} : result := 'Matrox DVCPRO codec';
    808801860 {DV50} : result := 'Matrox DVCPRO50 codec';
      4412996 {DVC } : result := 'MainConcept DV Codec';
   1346590276 {DVCP} : result := 'Sony Digital Video (DV)';
    843404868 {DVE2} : result := 'DVE-2 Videoconferencing Codec';
   1145591364 {DVHD} : result := 'DV 1125 lines at 30.00 Hz or 1250 lines at 25.00 Hz';
   1095587396 {DVMA} : result := 'Darim Vision DVMPEG';
    827545156 {DVS1} : result := 'DV compressed in SD (SDL)';
   1146312260 {DVSD} : result := 'Sony Digital Video (DV) 525 lines at 29.97 Hz or 625 lines at 25.00 Hz';
    827872836 {DVX1} : result := 'DVX1000SP Video Decoder';
    844650052 {DVX2} : result := 'DVX2000S Video Decoder';
    861427268 {DVX3} : result := 'DVX3000S Video Decoder';
    808802372 {DX50} : result := 'DivX 5.0 codec';
    827611204 {DXT1} : result := 'DirectX Compressed Texture';
    844388420 {DXT2} : result := 'DirectX Compressed Texture';
    861165636 {DXT3} : result := 'DirectX Compressed Texture';
    877942852 {DXT4} : result := 'DirectX Compressed Texture';
    894720068 {DXT5} : result := 'DirectX Compressed Texture';
   1129601092 {DXTC} : result := 'DirectX Texture Compression';
    810634053 {EKQ0} : result := 'Else graphics card codec';
    810241093 {ELK0} : result := 'Else graphics card codec';
   1446137157 {EM2V} : result := 'Etymonix MPEG-2 I-frame';
   1346589509 {ESCP} : result := 'Eidos Technologies Escape codec';
    827741253 {ETV1} : result := 'eTreppid Video Codec';
    844518469 {ETV2} : result := 'eTreppid Video Codec';
   1129731141 {ETVC} : result := 'eTreppid Video Codec';
   1347046470 {FLJP} : result := 'Field Encoded Motion JPEG (Targa emulation)';
   1096241734 {FRWA} : result := 'Darim Vision Forward Motion JPEG with Alpha-channel';
   1146573382 {FRWD} : result := 'Darim Vision Forward Motion JPEG';
   1415008838 {FRWT} : result := 'Darim Vision Forward Motion JPEG';
   1431786054 {FRWU} : result := 'Darim Vision Forward Uncompressed';
    826693190 {FVF1} : result := 'Fractal Video Frame';
   1464227398 {FVFW} : result := 'ff MPEG-4 based on XviD codec';
   1465535559 {GLZW} : result := 'Motion LZW by gabest@freemail.hu';
   1195724871 {GPEG} : result := 'Motion JPEG by gabest@freemail.hu (with floating point)';
   1414289223 {GWLT} : result := 'Microsoft Greyscale WLT DIB';
    808858184 {H260} : result := 'H.260';
    825635400 {H261} : result := 'H.261';
    842412616 {H262} : result := 'H.262';
    859189832 {H263} : result := 'Intel ITU H.263';
    875967048 {H264} : result := 'H.264';
    892744264 {H265} : result := 'H.265';
    909521480 {H266} : result := 'H.266';
    926298696 {H267} : result := 'H.267';
    943075912 {H268} : result := 'H.268';
    959853128 {H269} : result := 'H.263 for POTS-based videoconferencing';
   1431914056 {HFYU} : result := 'Huffman Lossless Codec YUV and RGB formats (with Alpha-channel)';
   1380142408 {HMCR} : result := 'Rendition Motion Compensation Format';
   1381125448 {HMRR} : result := 'Rendition Motion Compensation Format';
    859189833 {I263} : result := 'Intel ITU H.263';
    808596553 {I420} : result := 'Intel Indeo 4 H.263';
      5128521 {IAN } : result := 'Indeo 4 (RDX) Codec';
   1398161737 {IAVS} : result := 'interleaved audio and video stream';
   1112294217 {ICLB} : result := 'CellB Videoconferencing Codec';
   1380927305 {IGOR} : result := 'Power DVD';
   1196444233 {IJPG} : result := 'Intergraph JPEG';
   1129729097 {ILVC} : result := 'Intel Layered Video';
   1381387337 {ILVR} : result := 'ITU H.263+ Codec';
   1447317577 {IPDV} : result := 'Giga AVI DV Codec';
    825381449 {IR21} : result := 'Intel Indeo 2.1';
   1463898697 {IRAW} : result := 'Intel YUV Uncompressed';
   1448695113 {IUYV} : result := 'Interlaced version of UYVY (line order 0, 2, 4,....,1, 3, 5....)';
    808670793 {IV30} : result := 'Intel Indeo Video 3';
    825448009 {IV31} : result := 'Intel Indeo Video 3.1';
    842225225 {IV32} : result := 'Intel Indeo Video 3.2';
    859002441 {IV33} : result := 'Intel Indeo Video 3.3';
    875779657 {IV34} : result := 'Intel Indeo Video 3.4';
    892556873 {IV35} : result := 'Intel Indeo Video 3.5';
    909334089 {IV36} : result := 'Intel Indeo Video 3.6';
    926111305 {IV37} : result := 'Intel Indeo Video 3.7';
    942888521 {IV38} : result := 'Intel Indeo Video 3.8';
    959665737 {IV39} : result := 'Intel Indeo Video 3.9';
    808736329 {IV40} : result := 'Intel Indeo Video 4.0';
    825513545 {IV41} : result := 'Intel Indeo Video 4.1';
    842290761 {IV42} : result := 'Intel Indeo Video 4.2';
    859067977 {IV43} : result := 'Intel Indeo Video 4.3';
    875845193 {IV44} : result := 'Intel Indeo Video 4.4';
    892622409 {IV45} : result := 'Intel Indeo Video 4.5';
    909399625 {IV46} : result := 'Intel Indeo Video 4.6';
    926176841 {IV47} : result := 'Intel Indeo Video 4.7';
    942954057 {IV48} : result := 'Intel Indeo Video 4.8';
    959731273 {IV49} : result := 'Intel Indeo Video 4.9';
    808801865 {IV50} : result := 'Intel Indeo Video 5.0 Wavelet';
    825514313 {IY41} : result := 'Interlaced version of Y41P (line order 0, 2, 4,....,1, 3, 5....)';
    827677001 {IYU1} : result := '12 bit format used in mode 2 of the IEEE 1394 Digital Camera 1.04 spec';
    844454217 {IYU2} : result := '24 bit format used in mode 2 of the IEEE 1394 Digital Camera 1.04 spec';
   1448433993 {IYUV} : result := 'Intel Indeo iYUV 4:2:0';
   1195724874 {JPEG} : result := 'Still Image JPEG DIB';
   1279742026 {JPGL} : result := 'DIVIO JPEG Light for WebCams';
   1129729355 {KMVC} : result := 'Karl Morton Video Codec';
   1145128268 {LEAD} : result := 'LEAD Video Codec';
   1196444236 {LJPG} : result := 'LEAD Motion JPEG Codec';
   1297503052 {LSVM} : result := 'Vianet Lighting Strike Vmail (Streaming)';
    825635405 {M261} : result := 'Microsoft H.261';
    859189837 {M263} : result := 'Microsoft H.263';
    844313677 {M4S2} : result := 'Microsoft MPEG-4 (hacked MS MPEG-4)';
    842089293 {MC12} : result := 'ATI Motion Compensation Format';
   1296122701 {MCAM} : result := 'ATI Motion Compensation Format';
   1146504269 {MDVD} : result := 'Alex MicroDVD Video (hacked MS MPEG-4)';
   1127369293 {MJ2C} : result := 'Morgan Multimedia JPEG2000 Compression';
   1095780941 {MJPA} : result := 'Pinnacle Motion JPEG with Alpha-channel';
   1112558157 {MJPB} : result := 'Motion JPEG codec';
   1196444237 {MJPG} : result := 'IBM Motion JPEG including Huffman Tables';
   1397050701 {MMES} : result := 'Matrox MPEG-2 I-frame';
    842289229 {MP42} : result := 'Microsoft MPEG-4 V2';
    859066445 {MP43} : result := 'Microsoft MPEG-4 V3';
   1395937357 {MP4S} : result := 'Microsoft MPEG-4 (hacked MS MPEG-4)';
   1446269005 {MP4V} : result := 'Microsoft MPEG-4 (hacked MS MPEG-4)';
   1195724877 {MPEG} : result := 'Chromatic MPEG 1 Video I Frame';
    826757197 {MPG1} : result := 'FFmpeg-1';
    843534413 {MPG2} : result := 'FFmpeg-1';
    860311629 {MPG3} : result := 'Same as Low motion DivX MPEG-4';
    877088845 {MPG4} : result := 'Microsoft MPEG-4 V1';
   1229410381 {MPGI} : result := 'Sigma Design MPEG-1 I-frame';
   1196314701 {MPNG} : result := 'Motion PNG codec';
   1094931021 {MRCA} : result := 'FAST Multimedia MR Codec';
   1162629709 {MRLE} : result := 'Microsoft Run Length Encoding';
    827544397 {MSS1} : result := 'Windows Screen Video';
   1129730893 {MSVC} : result := 'Microsoft Video 1';
   1213879117 {MSZH} : result := 'Lossless codec (ZIP compression)';
    827872333 {MTX1} : result := 'Matrox codec';
    844649549 {MTX2} : result := 'Matrox codec';
    861426765 {MTX3} : result := 'Matrox codec';
    878203981 {MTX4} : result := 'Matrox codec';
    894981197 {MTX5} : result := 'Matrox codec';
    911758413 {MTX6} : result := 'Matrox codec';
    928535629 {MTX7} : result := 'Matrox codec';
    945312845 {MTX8} : result := 'Matrox codec';
    962090061 {MTX9} : result := 'Matrox codec';
    827742029 {MWV1} : result := 'Aware Motion Wavelets';
   1230389582 {NAVI} : result := 'nAVI video codec (hacked MS MPEG-4)';
    808473678 {NT00} : result := 'NewTek LigtWave HDTV YUV with Alpha-channel';
    827216974 {NTN1} : result := 'Nogatech Video Compression 1';
    827741518 {NUV1} : result := 'NuppelVideo';
    810767950 {NVS0} : result := 'Nvidia texture compression format';
    827545166 {NVS1} : result := 'Nvidia texture compression format';
    844322382 {NVS2} : result := 'Nvidia texture compression format';
    861099598 {NVS3} : result := 'Nvidia texture compression format';
    877876814 {NVS4} : result := 'Nvidia texture compression format';
    894654030 {NVS5} : result := 'Nvidia texture compression format';
    810833486 {NVT0} : result := 'Nvidia texture compression format';
    827610702 {NVT1} : result := 'Nvidia texture compression format';
    844387918 {NVT2} : result := 'Nvidia texture compression format';
    861165134 {NVT3} : result := 'Nvidia texture compression format';
    877942350 {NVT4} : result := 'Nvidia texture compression format';
    894719566 {NVT5} : result := 'Nvidia texture compression format';
   1129727056 {PDVC} : result := 'Panasonic DV codec';
   1448494928 {PGVV} : result := 'Radius Video Vision Telecast (adaptive JPEG)';
   1330464848 {PHMO} : result := 'Photomotion';
    827148624 {PIM1} : result := 'Pegasus Imaging codec';
    843925840 {PIM2} : result := 'Pegasus Imaging codec';
   1246579024 {PIMJ} : result := 'Pegasus Imaging PICvideo Lossless JPEG';
   1514493520 {PVEZ} : result := 'Horizons Technology PowerEZ codec';
   1296914000 {PVMM} : result := 'PacketVideo Corporation MPEG-4';
    844584528 {PVW2} : result := 'Pegasus Imaging Wavelet 2000';
    808333649 {Q1.0} : result := 'Q-Team QPEG 1.0';
   1195724881 {QPEG} : result := 'Q-Team QPEG 1.1';
   1363497041 {QPEQ} : result := 'Q-Team QPEG 1.1';
      5718354 {RAW } : result := 'Full Frames (Uncompressed)';
      4343634 {RGB } : result := 'Full Frames (Uncompressed)';
   1094862674 {RGBA} : result := 'Raw RGB with alpha';   /*VLC_CODEC_RGBA*/
   1413629778 {RGBT} : result := 'Uncompressed RGB with transparency';
    876956754 {RLE4} : result := 'Run length encoded 4bpp RGB image';
    944065618 {RLE8} : result := 'Run length encoded 8bpp RGB image';
      4541522 {RLE } : result := 'Raw RGB with arbitrary sample packing within a pixel';
    877677906 {RMP4} : result := 'REALmagic MPEG-4 Video Codec';
   1096437842 {RPZA} : result := 'Apple Video 16 bit "road pizza"';
    825381970 {RT21} : result := 'Intel Real Time Video 2.1';
    809784658 {RUD0} : result := 'Rududu video codec';
    808539730 {RV10} : result := 'RealVideo codec';
    858871378 {RV13} : result := 'RealVideo codec';
    808605266 {RV20} : result := 'RealVideo G2';
    808670802 {RV30} : result := 'RealVideo 8';
      5789266 {RVX } : result := 'Intel RDX';
    842150995 {S422} : result := 'VideoCap C210 YUV Codec';
   1128481875 {SDCC} : result := 'Sun Digital Camera Codec';
   1129137747 {SFMC} : result := 'Crystal Net SFM Codec';
   1196444243 {SJPG} : result := 'White Pine (ex Paradigm Matrix) Motion JPEG';
      4410707 {SMC } : result := 'Apple Graphics (SMC) codec (256 color)';
   1129532755 {SMSC} : result := 'Radius proprietary codec';
   1146309971 {SMSD} : result := 'Radius proprietary codec';
   1448299859 {SMSV} : result := 'WorldConnect Wavelet Streaming Video';
   1195987027 {SPIG} : result := 'Radius Spigot';
   1129074771 {SPLC} : result := 'Splash Studios ACM Audio Codec';
    844779859 {SQZ2} : result := 'Microsoft VXTreme Video Codec V2';
   1096176723 {STVA} : result := 'ST CMOS Imager Data (Bayer)';
   1112953939 {STVB} : result := 'ST CMOS Imager Data (Nudged Bayer)';
   1129731155 {STVC} : result := 'ST CMOS Imager Data (Bunched)';
   1482052691 {STVX} : result := 'ST CMOS Imager Data (Extended)';
   1498829907 {STVY} : result := 'ST CMOS Imager Data (Extended with Correction Data)';
    808539731 {SV10} : result := 'Sorenson Media Video R1';
    827414099 {SVQ1} : result := 'Sorenson Video (Apple Quicktime 3)';
    860968531 {SVQ3} : result := 'Sorenson Video 3 (Apple Quicktime 5)';
    808596564 {T420} : result := 'Toshiba YUV 4:2:0';
   1397574740 {TLMS} : result := 'TeraLogic Motion Infraframe Codec A';
   1414745172 {TLST} : result := 'TeraLogic Motion Infraframe Codec B';
    808602964 {TM20} : result := 'Duck TrueMotion 2.0';
   1093815636 {TM2A} : result := 'Duck TrueMotion Archiver 2.0';
   1479691604 {TM2X} : result := 'Duck TrueMotion 2X';
   1128877396 {TMIC} : result := 'TeraLogic Motion Intraframe Codec 2';
   1414483284 {TMOT} : result := 'TrueMotion Video Compression';
    808604244 {TR20} : result := 'Duck TrueMotion RT 2.0';
   1128485716 {TSCC} : result := 'TechSmith Screen Capture Codec';
    808539732 {TV10} : result := 'Tecomac Low-Bit Rate Codec';
   1246582356 {TVMJ} : result := 'Field Encoded Motion JPEG (Targa emulation)';
   1311791444 {TY0N} : result := 'Trident Decompression Driver';
   1127373140 {TY2C} : result := 'Trident Decompression Driver';
   1311922516 {TY2N} : result := 'Trident Decompression Driver';
    859189845 {U263} : result := 'UB Video StreamForce H.263';
   1146045269 {UCOD} : result := 'ClearVideo (fractal compression-based codec)';
   1230261333 {ULTI} : result := 'IBM Corp. Ultimotion';
   1447975253 {UYNV} : result := 'A direct copy of UYVY registered by NVidia to work around problems in some old codecs which did not like hardware which offered more than 2 UYVY surfaces';
   1347836245 {UYVP} : result := 'YCbCr 4:2:2 extended precision 10-bits per component in U0Y0V0Y1 order';
   1498831189 {UYVY} : result := 'YUV 4:2:2 (Y sample at every pixel, U and V sampled at every second pixel horizontally on each line)';
    825635414 {V261} : result := 'Lucent VX2000S';
    842150998 {V422} : result := 'Vitec Multimedia YUV 4:2:2 as for UYVY but with different component ordering within the u_int32 macropixel';
    892679766 {V655} : result := 'Vitec Multimedia 16 bit YUV 4:2:2 (6:5:5) format';
    827474774 {VCR1} : result := 'ATI VCR 1.0';
    844251990 {VCR2} : result := 'ATI VCR 2.0 (MPEG YV12)';
    861029206 {VCR3} : result := 'ATI VCR 3.0';
    877806422 {VCR4} : result := 'ATI VCR 4.0';
    894583638 {VCR5} : result := 'ATI VCR 5.0';
    911360854 {VCR6} : result := 'ATI VCR 6.0';
    928138070 {VCR7} : result := 'ATI VCR 7.0';
    944915286 {VCR8} : result := 'ATI VCR 8.0';
    961692502 {VCR9} : result := 'ATI VCR 9.0';
   1413694550 {VDCT} : result := 'Video Maker Pro DIB';
   1297040470 {VDOM} : result := 'VDOnet VDOWave';
   1464812630 {VDOW} : result := 'VDOLive (H.263)';
   1515471958 {VDTZ} : result := 'Darim Vision VideoTizer YUV';
   1481656150 {VGPX} : result := 'Alaris VGPixel Codec';
   1396984150 {VIDS} : result := 'Vitec Multimedia YUV 4:2:2 codec';
   1346783574 {VIFP} : result := 'Virtual Frame API codec (VFAPI)';
    827738454 {VIV1} : result := 'Vivo H.263';
    844515670 {VIV2} : result := 'Vivo H.263';
   1331054934 {VIVO} : result := 'Vivo H.263';
   1280854358 {VIXL} : result := 'miroVideo XL';
    827739222 {VLV1} : result := 'VideoLogic codec';
    808669270 {VP30} : result := 'On2 (ex Duck TrueMotion) VP3';
    825446486 {VP31} : result := 'On2 (ex Duck TrueMotion) VP3';
   1261525078 {VX1K} : result := 'Lucent VX1000S Video Codec';
   1261590614 {VX2K} : result := 'Lucent VX2000S Video Codec';
   1347639382 {VXSP} : result := 'Lucent VX1000SP Video Codec';
   1129726551 {WBVC} : result := 'Winbond W9960 codec';
   1296123991 {WHAM} : result := 'Microsoft Video 1';
   1481525591 {WINX} : result := 'Winnov Software Compression';
   1196444247 {WJPG} : result := 'Winbond JPEG';
    827739479 {WMV1} : result := 'Windows Media Video 7';
    844516695 {WMV2} : result := 'Windows Media Video 8';
    861293911 {WMV3} : result := 'Windows Media Video 9';
    827739735 {WNV1} : result := 'WinNow Videum Hardware Compression';
    859189848 {X263} : result := 'Xirlink H.263';
    810962008 {XLV0} : result := 'NetXL Inc. XL Video Decoder';
   1196445016 {XMPG} : result := 'XING MPEG (I frame only)';
   1145656920 {XVID} : result := 'XviD MPEG-4 codec';
    825307737 {Y211} : result := 'Packed YUV format with Y sampled at every second pixel across each line and U and V sampled at every fourth pixel';
    825308249 {Y411} : result := 'YUV 4:1:1 Packed';
   1110520921 {Y41B} : result := 'YUV 4:1:1 Planar';
   1345401945 {Y41P} : result := 'Conexant (ex Brooktree) YUV 4:1:1 Raw';
   1412510809 {Y41T} : result := 'Format as for Y41P but the lsb of each Y component is used to signal pixel transparency';
    842151001 {Y422} : result := 'Direct copy of UYVY as used by ADS Technologies Pyro WebCam firewire camera';
   1110586457 {Y42B} : result := 'YUV 4:2:2 Planar';
   1412576345 {Y42T} : result := 'Format as for UYVY but the lsb of each Y component is used to signal pixel transparency';
    808466521 {Y800} : result := 'Simple grayscale video';
    536885337 {Y8  } : result := 'Simple grayscale video';
    842089305 {YC12} : result := 'Intel YUV12 Codec';
   1447974233 {YUNV} : result := 'A direct copy of YUY2 registered by NVidia to work around problems in some old codecs which did not like hardware which offered more than 2 YUY2 surfaces';
    945182041 {YUV8} : result := 'Winnov Caviar YUV8';
    961959257 {YUV9} : result := 'Intel YUV9';
   1347835225 {YUVP} : result := 'YCbCr 4:2:2 extended precision 10-bits per component in Y0U0Y1V0 order';
    844715353 {YUY2} : result := 'YUV 4:2:2 as for UYVY but with different component ordering within the u_int32 macropixel';
   1448695129 {YUYV} : result := 'Canopus YUV format';
    842094169 {YV12} : result := 'ATI YVU12 4:2:0 Planar';
    961893977 {YVU9} : result := 'Brooktree YVU9 Raw (YVU9 Planar)';
   1431918169 {YVYU} : result := 'YUV 4:2:2 as for UYVY but with different component ordering within the u_int32 macropixel';
   1112099930 {ZLIB} : result := 'Lossless codec (ZIP compression)';
   1195724890 {ZPEG} : result := 'Metheus Video Zipper';