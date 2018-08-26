# Clocks

## Critical clocks

- `ddrphycfg_sel`
- `axi_sel` - feeds the main AXI bus.
- `infra_dramc_f26m` - without this, you will get severe memory corruption.
- `infra_dramc_b_f26m` - without this, you will get memory corruption, mostly single-bit flips.

## Clocks missing from the mainline

This list is not complete.

- The `mem_sel` MUX
- `ARMCAXPLL`s (the PLLs feeding into the actual processor)

## Functionality missing from the mainline

DCM / frequency hopping for clocks

## Clocks, gates and MUXes grouped by subsystem

This section is highly incomplete.

### Main

| Clock     | Type        | Description                                                                                                                  |
| --------- | ----------- | ---------------------------------------------------------------------------------------------------------------------------- |
| `clk26m`  | Fixed clock | The main clock from which all clocks are derived from. Runs at 26MHz.                                                        |
| `univpll` | PLL         | PLL used for various unrelated functions, e.g. camera, USB, and Mali.                                                        |
| `mainpll` | PLL         | PLL used for various unrelated functions, e.g. audio, SPM, DRAM, DVFS, I2C, modem, PWM, general-purpose timer, SEJ, GCE, ... |
| `axi_sel` | MUX         | Selects the clock for the main AXI bus.                                                                                      |

### Memory

| Clock                | Type | Description                                                                                 |
| -------------------- | ---- | ------------------------------------------------------------------------------------------- |
| `ddrphycfg_sel`      | MUX  | ?                                                                                           |
| `mem_sel`            | MUX  | ? - Missing from mainline. Presend and marked as critical for other CPU models in mainline. |
| `infra_dramc_f26m`   | Gate | ?                                                                                           |
| `infra_dramc_b_f26m` | Gate | Disabling this results in single-bit flips. Probably related to DRAM refresh.               |
| `infra_dramc_conf`   | Gate | ?                                                                                           |
| `infra_dramc_b_conf` | Gate | ?                                                                                           |

### Audio

| Clock   | Type | Description |
| ------- | ---- | ----------- |
| `apll1` | PLL  | Audio PLL   |
| `apll2` | PLL  | Audio PLL   |

## Clocks on Android

### `pg_*` clocks

The clocks prefixed with `pg_` are not actual clocks, but SCP power domains
represented as clocks instead of power domains. On mainline, these are
registered as actual power domains.

### Dump of clocks running on Android (`/sys/kernel/debug/clk/clk_summary`)

```
   clock                         enable_cnt  prepare_cnt        rate   accuracy   phase
----------------------------------------------------------------------------------------
 clk26m                                   5           12    26000000          0 0
    apll2                                 0            2   196608000          0 0
       apll2_ck                           0            3   196608000          0 0
          audio_h_sel                     0            2   196608000          0 0
             audio_pdn_adc_hires          0            1   196608000          0 0
             audio_pdn_adc_hires_tml      0            1   196608000          0 0
          aud_2_sel                       0            3   196608000          0 0
             audio_pdn_24m                0            1   196608000          0 0
             audio_pdn_apll2_tuner        0            1   196608000          0 0
    apll1                                 0            2   180633600          0 0
       apll1_ck                           0            2   180633600          0 0
          aud_1_sel                       0            3   180633600          0 0
             audio_pdn_22m                0            1   180633600          0 0
             audio_pdn_apll_tuner         0            1   180633600          0 0
    vdecpll                               0            1   338000000          0 0
       vdecpll_ck                         0            1   338000000          0 0
          vdec_sel                        0            1   338000000          0 0
             vdec_cken                    0            1   338000000          0 0
             vdec_active                  0            0   338000000          0 0
             vdec_cken_eng                0            0   338000000          0 0
    codecpll                              0            1   325000000          0 0
       codecpll_ck                        0            1   325000000          0 0
          venc_sel                        0            1   325000000          0 0
             venc_3                       0            0   325000000          0 0
             venc_2                       0            0   325000000          0 0
             venc_1                       0            1   325000000          0 0
          codecpll_d2                     0            0   162500000          0 0
    mpll                                  0            0   104000000          0 0
    tvdpll                                0            1   594000184          0 0
       tvdpll_ck                          0            5   594000184          0 0
          tvdpll_d16                      0            1    37125011          0 0
          tvdpll_d8                       0            1    74250023          0 0
          tvdpll_d4                       0            2   148500046          0 0
             dpi0_sel                     0            2   148500046          0 0
                mm_dpi_interface_clock    0            1   148500046          0 0
          tvdpll_d2                       0            1   297000092          0 0
    imgpll                                1            1   325000000          0 0
       imgpll_ck                          1            2   325000000          0 0
          mjc_sel                         0            2   325000000          0 0
             mm_larb4_axi_asif_mjc_clock  0            0   325000000          0 0
             mjc_larb4_asif               0            1   325000000          0 0
             mjc_fake_engine              0            0   325000000          0 0
             mjc_top_clk_2                0            0   325000000          0 0
             mjc_top_clk_1                0            0   325000000          0 0
             mjc_top_clk_0                0            0   325000000          0 0
             mjc_smi_larb                 0            1   325000000          0 0
          mm_sel                         13           28   325000000          0 0
             vdec_larb1_cken              0            1   325000000          0 0
             img_larb6                    0            1   325000000          0 0
             img_dip                      0            0   325000000          0 0
             img_dpe                      0            0   325000000          0 0
             img_fdvt                     0            0   325000000          0 0
             mm_fake_eng2                 0            0   325000000          0 0
             mm_disp_ovl0_mout_clock      0            1   325000000          0 0
             mm_larb4_axi_asif_mm_clock   0            0   325000000          0 0
             mm_dpi_mm_clock              0            1   325000000          0 0
             mm_dsi1_mm_clock             0            1   325000000          0 0
             mm_dsi0_mm clock             1            1   325000000          0 0
             mm_disp_split                0            1   325000000          0 0
             mm_disp_dsc                  0            1   325000000          0 0
             mm_disp_ufoe                 1            1   325000000          0 0
             mm_disp_dither               1            1   325000000          0 0
             mm_disp_od                   1            1   325000000          0 0
             mm_disp_gamma                1            1   325000000          0 0
             mm_disp_aal                  1            1   325000000          0 0
             mm_disp_ccorr                1            1   325000000          0 0
             mm_disp_color                1            1   325000000          0 0
             mm_disp_wdma1                0            1   325000000          0 0
             mm_disp_wdma0                0            1   325000000          0 0
             mm_disp_rdma1                0            1   325000000          0 0
             mm_disp_rdma0                1            1   325000000          0 0
             mm_disp_ovl1_2l              0            1   325000000          0 0
             mm_disp_ovl0_2l              0            1   325000000          0 0
             mm_disp_ovl1                 0            1   325000000          0 0
             mm_disp_ovl0                 0            1   325000000          0 0
             mm_fake_eng                  0            0   325000000          0 0
             mm_mdp_wrot1                 0            0   325000000          0 0
             mm_mdp_wrot0                 0            0   325000000          0 0
             mm_mdp_wdma                  0            0   325000000          0 0
             mm_mdp_color                 0            0   325000000          0 0
             mm_mdp_tdshp                 0            0   325000000          0 0
             mm_mdp_rsz2                  0            0   325000000          0 0
             mm_mdp_rsz1                  0            0   325000000          0 0
             mm_mdp_rsz0                  0            0   325000000          0 0
             mm_mdp_rdma1                 0            0   325000000          0 0
             mm_mdp_rdma0                 0            0   325000000          0 0
             mm_cam_mdp                   0            0   325000000          0 0
             mm_smi_larb5                 1            2   325000000          0 0
             mm_smi_larb0                 1            2   325000000          0 0
             mm_smi_common                1            2   325000000          0 0
             cam_larb2                    0            1   325000000          0 0
             cam_camsys                   0            0   325000000          0 0
             cam_seninf                   0            0   325000000          0 0
             cam_camsv0                   0            0   325000000          0 0
             cam_camsv1                   0            0   325000000          0 0
             cam_camsv2                   0            0   325000000          0 0
             venc_0                       0            0   325000000          0 0
             infra_l2c_sram               0            0   325000000          0 0
          imgpll_d4                       0            0    81250000          0 0
          imgpll_d2                       0            0   162500000          0 0
    msdcpll                               0            2   383999878          0 0
       msdcpll_ck                         0            1   383999878          0 0
          msdcpll_d8                      0            0    47999984          0 0
          msdcpll_d4                      0            0    95999969          0 0
          msdcpll_d2                      0            1   191999939          0 0
             msdc30_1_sel                 0            1   191999939          0 0
                infra_msdc1               0            1   191999939          0 0
       msdc50_0_sel                       0            1   383999878          0 0
          infra_msdc0                     0            1   383999878          0 0
    mfgpll                                0            0   500500000          0 0
       mfgpll_ck                          0            0   500500000          0 0
          mfg_sel                         0            0   500500000          0 0
             mfg_bg3d                     0            0   500500000          0 0
          mfgpll_d2                       0            0   250250000          0 0
    univpll                               2            3  1248000000          0 0
       univpll_ck                         0            0  1248000000          0 0
       univpll_d7                         0            0   178285714          0 0
       univpll_d26                        0            0    48000000          0 0
          camtg_sel                       0            0    48000000          0 0
             cam_camtg                    0            0    48000000          0 0
       ssusb_phy_48m_ck                   0            0  1248000000          0 0
       usb_phy48m_ck                      0            0  1248000000          0 0
       univpll_d2                         1            1   624000000          0 0
          univpll1_d8                     1            1    78000000          0 0
             usb20_sel                    1            1    78000000          0 0
                infra_icusb               1            1    78000000          0 0
          univpll1_d4                     0            0   156000000          0 0
          univpll1_d2                     0            0   312000000          0 0
       univpll_d3                         0            0   416000000          0 0
       univpll2_d2                        0            0   624000000          0 0
       univpll2_d4                        0            1   312000000          0 0
       univpll2_d8                        0            0   156000000          0 0
          mfg_52m_sel                     0            0   156000000          0 0
             infra_mfg_vcg                0            0   156000000          0 0
          msdc30_2_sel                    0            0   156000000          0 0
             infra_msdc2                  0            0   156000000          0 0
       univpll_d5                         1            1   249600000          0 0
          univpll3_d8                     0            0    31200000          0 0
          univpll3_d4                     0            0    62400000          0 0
          univpll3_d2                     1            1   124800000          0 0
             ssusb_top_sys_sel            1            2   124800000          0 0
                infra_ssusb_sys           1            1   124800000          0 0
    mainpll                               1            2  1092000000          0 0
       syspll_ck                          0            0  1092000000          0 0
       syspll_d2                          1            2   546000000          0 0
          syspll1_d16                     0            0    34125000          0 0
          syspll1_d8                      0            0    68250000          0 0
             spm_sel                      0            0    68250000          0 0
          syspll1_d4                      1            3   136500000          0 0
             bsi_spi_sel                  0            0   136500000          0 0
             aud_intbus_sel               0            1   136500000          0 0
             ulposc_axi_ck_mux            1            1   136500000          0 0
                axi_sel                   5            8   136500000          0 0
                   infra_dramc_b_conf     0            0   136500000          0 0
                   infra_dramc_conf       0            0   136500000          0 0
                   infra_vad_wrap_soc     0            0   136500000          0 0
                   infra_modem_temp_share 0            0   136500000          0 0
                   infra_ssusb_bus        1            1   136500000          0 0
                   infra_aes_top1         0            0   136500000          0 0
                   infra_aes_top0         0            0   136500000          0 0
                   infra_dvfs_spm1        0            0   136500000          0 0
                   infra_sys_cirq         0            0   136500000          0 0
                   infra_i2c5             0            1   136500000          0 0
                   infra_i2c3_arb         0            0   136500000          0 0
                   infra_i2c3_imm         0            0   136500000          0 0
                   infra_i2c2_arb         0            0   136500000          0 0
                   infra_i2c2_imm         0            0   136500000          0 0
                   infra_i2c_gpupm        0            0   136500000          0 0
                   infra_i2c_appm         1            2   136500000          0 0
                   infra_i2c4             0            0   136500000          0 0
                   infra_ccif_md          0            0   136500000          0 0
                   infra_audio            0            1   136500000          0 0
                   infra_ccif_ap          0            0   136500000          0 0
                   infra_device_apc       0            0   136500000          0 0
                   infra_ap_dma           1            2   136500000          0 0
                   infra_cldma            0            0   136500000          0 0
                   infra_ap_c2k_ccif_1    0            0   136500000          0 0
                   infra_ap_c2k_ccif_0    0            0   136500000          0 0
                   infra_cpum             0            0   136500000          0 0
                   infra_trng             0            0   136500000          0 0
                   infra_gcpu             0            0   136500000          0 0
                   infra_md2md_ccif_5     0            0   136500000          0 0
                   infra_md2md_ccif_4     0            0   136500000          0 0
                   infra_md2md_ccif_3     0            0   136500000          0 0
                   infra_btif             0            1   136500000          0 0
                   infra_md2md_ccif_2     0            0   136500000          0 0
                   infra_md2md_ccif_1     0            0   136500000          0 0
                   infra_md2md_ccif_0     0            0   136500000          0 0
                   infra_pwm              0            0   136500000          0 0
                   infra_pwm4             0            0   136500000          0 0
                   infra_pwm3             0            0   136500000          0 0
                   infra_pwm2             0            0   136500000          0 0
                   infra_pwm1             0            0   136500000          0 0
                   infra_pwm_hclk         0            0   136500000          0 0
                   infra_i2c3             0            0   136500000          0 0
                   infra_i2c2             0            0   136500000          0 0
                   infra_i2c1             0            0   136500000          0 0
                   infra_i2c0             0            0   136500000          0 0
                   infra_therm            1            1   136500000          0 0
                   infra_gce              1            1   136500000          0 0
                   infra_apxgpt           0            0   136500000          0 0
                   infra_sej              0            0   136500000          0 0
          syspll1_d2                      0            2   273000000          0 0
             anc_md32_sel                 0            2   273000000          0 0
                infra_anc_md32            0            1   273000000          0 0
             atb_sel                      0            0   273000000          0 0
             msdc50_0_hclk_sel            0            0   273000000          0 0
       syspll_d3                          0            0   364000000          0 0
          scp_sel                         0            0   364000000          0 0
             infra_scp                    0            0   364000000          0 0
          syspll2_d8                      0            0    45500000          0 0
          syspll2_d4                      0            0    91000000          0 0
          syspll2_d2                      0            0   182000000          0 0
          syspll_d3_d3                    0            0   121333333          0 0
       syspll_d5                          0            2   218400000          0 0
          syspll3_d4                      0            1    54600000          0 0
          syspll3_d2                      0            1   109200000          0 0
             spi_sel                      0            6   109200000          0 0
                infra_irtx                0            0   109200000          0 0
                infra_spi5                0            1   109200000          0 0
                infra_spi4                0            1   109200000          0 0
                infra_spi3                0            1   109200000          0 0
                infra_spi2                0            1   109200000          0 0
                infra_spi1                0            1   109200000          0 0
                infra_spi                 0            1   109200000          0 0
             ddrphycfg_sel                0            0   109200000          0 0
       syspll_d7                          0            0   156000000          0 0
          syspll4_d4                      0            0    39000000          0 0
          syspll4_d2                      0            0    78000000          0 0
    pmicspi_sel                           0            0    26000000          0 0
       infra_pmic_conn                    0            0    26000000          0 0
       infra_pmic_md                      0            0    26000000          0 0
       infra_pmic_ap                      0            0    26000000          0 0
    audio_sel                             8            6    26000000          0 0
       audio_pdn_afe                      0            1    26000000          0 0
       audio_pdn_adc                      0            1    26000000          0 0
       audio_pdn_dac                      0            1    26000000          0 0
       audio_pdn_dac_predis               0            1    26000000          0 0
       audio_pdn_tml                      0            1    26000000          0 0
    uart_sel                              1            1    26000000          0 0
       infra_uart3                        0            0    26000000          0 0
       infra_uart2                        0            0    26000000          0 0
       infra_uart1                        0            0    26000000          0 0
       infra_uart0                        1            1    26000000          0 0
 clk_null                                 2            4           0          0 0
    mm_dsi1_interface_clock               0            1           0          0 0
    mm_dsi0_interface_clock               1            1           0          0 0
    infra_anc_md32_32k                    0            1           0          0 0
    ulposc                                1            1           0          0 0
       infra_pmic_tmr                     0            0           0          0 0
       ulposc_ck_org                      1            2           0          0 0
          ulposc_d10                      0            1           0          0 0
          ulposc_ck                       1            4           0          0 0
             ulposc_d8                    1            2           0          0 0
                pwm_sel                   1            2           0          0 0
                   infra_disp_pwm         1            1           0          0 0
             ulposc_d4                    0            1           0          0 0
             ulposc_d3                    0            1           0          0 0
             ulposc_d2                    0            1           0          0 0
                ulposc_spi_ck_mux         0            0           0          0 0
                ulposc_axi_ck_mux_pre     0            0           0          0 0
 pg_c2k                                   1            1           0          0 0
 pg_audio                                 0            0           0          0 0
 pg_ven                                   0            0           0          0 0
 pg_mjc                                   0            0           0          0 0
 pg_mfg_async                             0            0           0          0 0
    pg_mfg                                0            0           0          0 0
       pg_mfg_core0                       0            0           0          0 0
       pg_mfg_core1                       0            0           0          0 0
       pg_mfg_core2                       0            0           0          0 0
       pg_mfg_core3                       0            0           0          0 0
 pg_vde                                   0            0           0          0 0
 pg_isp                                   0            0           0          0 0
 pg_dis                                   1            1           0          0 0
 pg_conn                                  1            1           0          0 0
 pg_md1                                   1            1           0          0 0
 infra_audio_26m_pad_top                  0            1           0          0 0
 infra_audio_26m                          0            1           0          0 0
 infra_ssusb_ref                          2            2           0          0 0
 infra_dramc_b_f26m                       0            0           0          0 0
 infra_dramc_f26m                         0            0           0          0 0
 infra_auxadc                             1            1           0          0 0
 infra_fhctl                              0            0           0          0 0
 infra_sej_13m                            0            0           0          0 0
 mem_sel                                  0            0           0          0 0
 ```
