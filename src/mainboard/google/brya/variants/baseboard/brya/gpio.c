/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <baseboard/gpio.h>
#include <baseboard/variants.h>
#include <commonlib/helpers.h>
#include <soc/gpio.h>
#include <vendorcode/google/chromeos/chromeos.h>

/* Pad configuration in ramstage */
static const struct pad_config gpio_table[] = {
	/* A0 thru A5, A9 and A10 come configured out of reset, do not touch */
	/* A0  : ESPI_IO0 ==> ESPI_IO_0 */
	/* A1  : ESPI_IO1 ==> ESPI_IO_1 */
	/* A2  : ESPI_IO2 ==> ESPI_IO_2 */
	/* A3  : ESPI_IO3 ==> ESPI_IO_3 */
	/* A4  : ESPI_CS# ==> ESPI_CS_L */
	/* A5  : ESPI_ALERT0# ==> NC */
	PAD_NC(GPP_A5, NONE),
	/* A6  : ESPI_ALERT1# ==> SPKR_INT_L */
	PAD_CFG_GPI(GPP_A6, NONE, DEEP),
	/* A7  : SRCCLK_OE7# ==> WWAN_PCIE_WAKE_ODL */
	PAD_CFG_GPI_APIC(GPP_A7, NONE, PLTRST, LEVEL, INVERT),
	/* A8  : SRCCLKREQ7# ==> WWAN_RF_DISABLE_ODL */
	PAD_CFG_GPO(GPP_A8, 1, DEEP),
	/* A9  : ESPI_CLK ==> ESPI_CLK */
	/* A10 : ESPI_RESET# ==> ESPI_PCH_RST_EC_L */
	/* A11 : PMC_I2C_SDA ==> EN_SPKR_PA */
	PAD_CFG_GPO(GPP_A11, 1, DEEP),
	/* A12 : SATAXPCIE1 ==> EN_PP3300_WWAN */
	PAD_CFG_GPO(GPP_A12, 1, DEEP),
	/* A13 : PMC_I2C_SCL ==> GSC_PCH_INT_ODL */
	PAD_CFG_GPI_APIC(GPP_A13, NONE, PLTRST, LEVEL, INVERT),
	/* A14 : USB_OC1# ==> USB_C1_OC_ODL */
	PAD_CFG_NF(GPP_A14, NONE, DEEP, NF1),
	/* A15 : USB_OC2# ==> USB_C2_OC_ODL */
	PAD_CFG_NF(GPP_A15, NONE, DEEP, NF1),
	/* A16 : USB_OC3# ==> USB_A0_OC_ODL */
	PAD_CFG_NF(GPP_A16, NONE, DEEP, NF1),
	/* A17 : DISP_MISCC ==> EN_FCAM_PWR */
	PAD_CFG_GPO(GPP_A17, 1, DEEP),
	/* A18 : DDSP_HPDB ==> HDMI_HPD */
	PAD_CFG_NF(GPP_A18, NONE, DEEP, NF1),
	/* A19 : DDSP_HPD1 ==> USB_C2_AUX_DC_P */
	PAD_CFG_NF(GPP_A19, NONE, DEEP, NF6),
	/* A20 : DDSP_HPD2 ==> USB_C2_AUX_DC_N */
	PAD_CFG_NF(GPP_A20, NONE, DEEP, NF6),
	/* A21 : DDPC_CTRCLK ==> USB_C1_AUX_DC_P */
	PAD_CFG_NF(GPP_A21, NONE, DEEP, NF6),
	/* A22 : DDPC_CTRLDATA ==> USB_C1_AUX_DC_N */
	PAD_CFG_NF(GPP_A22, NONE, DEEP, NF6),
	/* A23 : ESPI_CS1# ==> AUD_HP_INT_L */
	PAD_CFG_GPI_INT(GPP_A23, NONE, PLTRST, EDGE_BOTH),

	/* B0  : SOC_VID0 */
	PAD_CFG_NF(GPP_B0, NONE, DEEP, NF1),
	/* B1  : SOC_VID1 */
	PAD_CFG_NF(GPP_B1, NONE, DEEP, NF1),
	/* B2  : VRALERT# ==> M2_SSD_PLA_L */
	PAD_CFG_GPO(GPP_B2, 1, PLTRST),
	/* B3  : PROC_GP2 ==> SAR2_INT_L */
	PAD_CFG_GPI_APIC(GPP_B3, NONE, PLTRST, LEVEL, NONE),
	/* B4  : PROC_GP3 ==> SSD_PERST_L */
	PAD_CFG_GPO(GPP_B4, 1, DEEP),
	/* B5  : ISH_I2C0_SDA ==> PCH_I2C_MISC_SDA */
	PAD_CFG_NF(GPP_B5, NONE, DEEP, NF2),
	/* B6  : ISH_I2C0_SCL ==> PCH_I2C_MISC_SCL */
	PAD_CFG_NF(GPP_B6, NONE, DEEP, NF2),
	/* B7  : ISH_12C1_SDA ==> PCH_I2C_TPM_SDA */
	PAD_CFG_NF(GPP_B7, NONE, DEEP, NF2),
	/* B8  : ISH_I2C1_SCL ==> PCH_I2C_TPM_SCL */
	PAD_CFG_NF(GPP_B8, NONE, DEEP, NF2),
	/* B9  : NC */
	PAD_NC(GPP_B9, NONE),
	/* B10 : NC */
	PAD_NC(GPP_B10, NONE),
	/* B11 : PMCALERT# ==> EN_PP3300_WLAN */
	PAD_CFG_GPO(GPP_B11, 1, DEEP),
	/* B12 : SLP_S0# ==> SLP_S0_L */
	PAD_CFG_NF(GPP_B12, NONE, DEEP, NF1),
	/* B13 : PLTRST# ==> PLT_RST_L */
	PAD_CFG_NF(GPP_B13, NONE, DEEP, NF1),
	/* B14 : SPKR ==> GPP_B14_STRAP */
	PAD_NC(GPP_B14, NONE),
	/* B15 : TIME_SYNC0 ==> FP_USER_PRES_FP_L */
	PAD_CFG_GPI(GPP_B15, NONE, PLTRST),
	/* B16 : I2C5_SDA ==> PCH_I2C_TCHPAD_SDA */
	PAD_CFG_NF(GPP_B16, NONE, DEEP, NF2),
	/* B17 : I2C5_SCL ==> PCH_I2C_TCHPAD_SCL */
	PAD_CFG_NF(GPP_B17, NONE, DEEP, NF2),
	/* B18 : ADR_COMPLETE ==> GPP_B18_STRAP */
	PAD_NC(GPP_B18, NONE),
	/* B19 : NC */
	PAD_NC(GPP_B19, NONE),
	/* B20 : NC */
	PAD_NC(GPP_B20, NONE),
	/* B21 : NC */
	PAD_NC(GPP_B21, NONE),
	/* B22 : NC */
	PAD_NC(GPP_B22, NONE),
	/* B23 : SML1ALERT# ==> PCHHOT_ODL_STRAP */
	PAD_NC(GPP_B23, NONE),

	/* C0  : SMBCLK ==> EN_PP3300_TCHSCR */
	PAD_CFG_GPO(GPP_C0, 1, DEEP),
	/* C1  : SMBDATA ==> USI_RST_L */
	PAD_CFG_GPO(GPP_C1, 0, DEEP),
	/* C2  : SMBALERT# ==> GPP_C2_STRAP */
	PAD_NC(GPP_C2, NONE),
	/* C3 : SML0CLK ==> EN_UCAM_PWR */
	PAD_CFG_GPO(GPP_C3, 0, DEEP),
	/* C4 : SML0DATA ==> EN_UCAM_SENR_PWR */
	PAD_CFG_GPO(GPP_C4, 0, DEEP),
	/* C5  : SML0ALERT# ==> GPP_C5_BOOT_STRAP0 */
	PAD_NC(GPP_C5, NONE),
	/* C6  : SML1CLK ==> USI_REPORT_EN */
	PAD_CFG_GPO(GPP_C6, 0, DEEP),
	/* C7  : SML1DATA ==> USI_INT */
	PAD_CFG_GPI_APIC(GPP_C7, NONE, PLTRST, LEVEL, NONE),

	/* D0  : ISH_GP0 ==> PCH_FP_BOOT0 */
	PAD_NC(GPP_D0, NONE),
	/* D1  : ISH_GP1 ==> FP_RST_ODL */
	PAD_CFG_GPO(GPP_D1, 1, DEEP),
	/* D2  : ISH_GP2 ==> EN_FP_PWR */
	PAD_CFG_GPO(GPP_D2, 1, DEEP),
	/* D3  : ISH_GP3 ==> WCAM_RST_L */
	PAD_CFG_GPO(GPP_D3, 0, DEEP),
	/* D4  : IMGCLKOUT0 ==> BT_DISABLE_L */
	PAD_CFG_GPO(GPP_D4, 1, DEEP),
	/* D5  : SRCCLKREQ0# ==> WWAN_DPR_SAR_ODL */
	PAD_CFG_GPO(GPP_D5, 1, DEEP),
	/* D6  : SRCCLKREQ1# ==> SSD_CLKREQ_ODL */
	PAD_CFG_NF(GPP_D6, NONE, DEEP, NF1),
	/* D7  : SRCCLKREQ2# ==> WLAN_CLKREQ_ODL */
	PAD_CFG_NF(GPP_D7, NONE, DEEP, NF1),
	/* D8  : SRCCLKREQ3# ==> SD_CLKREQ_ODL */
	PAD_CFG_NF(GPP_D8, NONE, DEEP, NF1),
	/* D9  : ISH_SPI_CS# ==> USB_C2_LSX_TX */
	PAD_CFG_NF(GPP_D9, NONE, DEEP, NF4),
	/* D10 : ISH_SPI_CLK ==> USB_C2_LSX_RX_STRAP */
	PAD_CFG_NF(GPP_D10, NONE, DEEP, NF4),
	/* D11 : ISH_SPI_MISO ==> EN_PP3300_SSD */
	PAD_CFG_GPO(GPP_D11, 1, DEEP),
	/* D12 : ISH_SPI_MOSI ==> GPP_D12_STRAP */
	PAD_NC(GPP_D12, NONE),
	/* D13 : ISH_UART0_RXD ==> CAM_PSW_L */
	PAD_CFG_GPI_INT(GPP_D13, NONE, PLTRST, EDGE_BOTH),
	/* D14 : ISH_UART0_TXD ==> SPKR_INT_L */
	PAD_CFG_GPI(GPP_D14, NONE, DEEP),
	/* D15 : ISH_UART0_RTS# ==> EN_WCAM_SENR_PWR */
	PAD_CFG_GPO(GPP_D15, 0, DEEP),
	/* D16 : ISH_UART0_CTS# ==> EN_WCAM_PWR */
	PAD_CFG_GPO(GPP_D16, 0, DEEP),
	/* D17 : UART1_RXD ==> SD_PE_PRSNT_L */
	PAD_CFG_GPI(GPP_D17, NONE, DEEP),
	/* D18 : UART1_TXD ==> SD_PE_RST_L */
	PAD_CFG_GPO(GPP_D18, 1, DEEP),
	/* D19 : I2S_MCLK1_OUT ==> I2S_MCLK_R */
	PAD_CFG_NF(GPP_D19, NONE, DEEP, NF1),

	/* E0  : see end of E group */
	/* E1  : THC0_SPI1_IO2 ==> MEM_STRAP_2 */
	PAD_CFG_GPI(GPP_E1, NONE, DEEP),
	/* E2  : THC0_SPI1_IO3 ==> MEM_STRAP_1 */
	PAD_CFG_GPI(GPP_E2, NONE, DEEP),
	/* E3  : PROC_GP0 ==> HPS_INT_ODL */
	PAD_CFG_GPI_IRQ_WAKE(GPP_E3, NONE, PLTRST, LEVEL, NONE),
	/* E4  : SATA_DEVSLP0 ==> USB4_BB_RT_FORCE_PWR */
	PAD_CFG_GPO(GPP_E4, 0, DEEP),
	/* E5  : SATA_DEVSLP1 ==> USB_A0_RT_RST_ODL */
	PAD_CFG_GPO(GPP_E5, 1, DEEP),
	/* E6  : THC0_SPI1_RST# ==> GPPE6_STRAP */
	PAD_NC(GPP_E6, NONE),
	/* E7  : PROC_GP1 ==> EN_HPS_PWR */
	PAD_CFG_GPO(GPP_E7, 1, DEEP),
	/* E8  : SLP_DRAM# ==> WIFI_DISABLE_L */
	PAD_CFG_GPO(GPP_E8, 1, DEEP),
	/* E9  : USB_OC0# ==> USB_C0_OC_ODL */
	PAD_CFG_NF(GPP_E9, NONE, DEEP, NF1),
	/* E10 : THC0_SPI1_CS# ==> WWAN_CONFIG0 */
	PAD_CFG_GPI(GPP_E10, NONE, DEEP),
	/* E11 : THC0_SPI1_CLK ==> MEM_STRAP_0 */
	PAD_CFG_GPI(GPP_E11, NONE, DEEP),
	/* E12 : THC0_SPI1_IO1 ==> MEM_STRAP_3 */
	PAD_CFG_GPI(GPP_E12, NONE, DEEP),
	/* E13 : THC0_SPI1_IO2 ==> MEM_CH_SEL */
	PAD_CFG_GPI(GPP_E13, NONE, DEEP),
	/* E14 : DDSP_HPDA ==> SOC_EDP_HPD */
	PAD_CFG_NF(GPP_E14, NONE, DEEP, NF1),
	/* E15 : RSVD_TP ==> PCH_WP_OD */
	PAD_CFG_GPI_GPIO_DRIVER(GPP_E15, NONE, DEEP),
	/* E16 : RSVD_TP ==> WWAN_RST_L */
	PAD_CFG_GPO(GPP_E16, 1, DEEP),
	/* E17 : THC0_SPI1_INT# ==> WWAN_CONFIG3 */
	PAD_CFG_GPI(GPP_E17, NONE, DEEP),
	/* E18 : DDP1_CTRLCLK ==> USB_C0_LSX_SOC_TX */
	PAD_CFG_NF(GPP_E18, NONE, DEEP, NF4),
	/* E19 : DDP1_CTRLDATA ==> USB0_C0_LSX_SOC_RX_STRAP */
	PAD_CFG_NF(GPP_E19, NONE, DEEP, NF4),
	/* E20 : DDP2_CTRLCLK ==> USB_C1_LSX_SOC_TX */
	PAD_CFG_NF(GPP_E20, NONE, DEEP, NF4),
	/* E21 : DDP2_CTRLDATA ==> USB_C1_LSX_SOC_RX_STRAP */
	PAD_CFG_NF(GPP_E21, NONE, DEEP, NF4),
	/* E22 : DDPA_CTRLCLK ==> USB_C0_AUX_DC_P */
	PAD_CFG_NF(GPP_E22, NONE, DEEP, NF6),
	/* E23 : DDPA_CTRLDATA ==> USB_C0_AUX_DC_N */
	PAD_CFG_NF(GPP_E23, NONE, DEEP, NF6),
	/* E0 : SATAXPCIE0 ==> WWAN_PERST_L
	   NB. Driven high here so that it is sequenced after WWAN_RST_L; a
	   PERST# signal would normally be reset by PLRST#, but here it will be
	   explicitly programmed during a power-down sequence. */
	PAD_CFG_GPO(GPP_E0, 1, DEEP),

	/* F0  : CNV_BRI_DT ==> CNV_BRI_DT_STRAP */
	PAD_CFG_NF(GPP_F0, NONE, DEEP, NF1),
	/* F1  : CNV_BRI_RSP ==> CNV_BRI_RSP */
	PAD_CFG_NF(GPP_F1, UP_20K, DEEP, NF1),
	/* F2  : CNV_RGI_DT ==> CNV_RGI_DT_STRAP */
	PAD_CFG_NF(GPP_F2, NONE, DEEP, NF1),
	/* F3  : CNV_RGI_RSP ==> CNV_RGI_RSP */
	PAD_CFG_NF(GPP_F3, UP_20K, DEEP, NF1),
	/* F4  : CNV_RF_RESET# ==> CNV_RF_RST_L */
	PAD_CFG_NF(GPP_F4, NONE, DEEP, NF1),
	/* F5  : MODEM_CLKREQ ==> CNV_CLKREQ0 */
	PAD_CFG_NF(GPP_F5, NONE, DEEP, NF3),
	/* F6  : CNV_PA_BLANKING ==> WWAN_WLAN_COEX3 */
	PAD_CFG_NF(GPP_F6, NONE, DEEP, NF1),
	/* F7  : GPPF7_STRAP */
	PAD_NC(GPP_F7, NONE),
	/* F8  : NC */
	PAD_NC(GPP_F8, NONE),
	/* F9  : BOOTMPC ==> SLP_S0_GATE_R */
	PAD_CFG_GPO(GPP_F9, 1, PLTRST),
	/* F10 : GPPF10_STRAP */
	PAD_NC(GPP_F10, DN_20K),
	/* F11 : THC1_SPI2_CLK ==> GSPI_PCH_CLK_FPMCU_R */
	PAD_CFG_NF(GPP_F11, NONE, DEEP, NF4),
	/* F12 : GSXDOUT ==> GSPI_PCH_DO_FPMCU_DI_R */
	PAD_CFG_NF(GPP_F12, NONE, DEEP, NF4),
	/* F13 : GSXDOUT ==> GSPI_PCH_DI_FPMCU_DO */
	PAD_CFG_NF(GPP_F13, NONE, DEEP, NF4),
	/* F14 : GSXDIN ==> TCHPAD_INT_ODL */
	PAD_CFG_GPI_IRQ_WAKE(GPP_F14, NONE, PLTRST, LEVEL, INVERT),
	/* F15 : GSXSRESET# ==> FPMCU_INT_L */
	PAD_CFG_GPI_IRQ_WAKE(GPP_F15, NONE, DEEP, LEVEL, INVERT),
	/* F16 : GSXCLK ==> GSPI_PCH_CS_FPMCU_R_L */
	PAD_CFG_NF(GPP_F16, NONE, DEEP, NF4),
	/* F17 : THC1_SPI2_RST# ==> EC_PCH_INT_ODL */
	PAD_CFG_GPI_IRQ_WAKE(GPP_F17, NONE, DEEP, LEVEL, INVERT),
	/* F18 : THC1_SPI2_INT# ==> EC_IN_RW_OD */
	PAD_CFG_GPI(GPP_F18, NONE, DEEP),
	/* F19 : SRCCLKREQ6# ==> M2_SSD_PLN_L */
	PAD_CFG_GPO(GPP_F19, 1, PLTRST),
	/* F20 : EXT_PWR_GATE# ==> UCAM_RST_L */
	PAD_CFG_GPO(GPP_F20, 0, DEEP),
	/* F21 : EXT_PWR_GATE2# ==> WWAN_FCPO_L */
	PAD_CFG_GPO(GPP_F21, 1, DEEP),
	/* F22 : NC */
	PAD_NC(GPP_F22, NONE),
	/* F23 : NC */
	PAD_NC(GPP_F23, NONE),

	/* H0  : GPPH0_BOOT_STRAP1 */
	PAD_NC(GPP_H0, NONE),
	/* H1  : GPPH1_BOOT_STRAP2 */
	PAD_NC(GPP_H1, NONE),
	/* H2  : GPPH2_BOOT_STRAP3 */
	PAD_NC(GPP_H2, NONE),
	/* H3  : SX_EXIT_HOLDOFF# ==> WLAN_PCIE_WAKE_ODL */
	PAD_CFG_GPI(GPP_H3, NONE, DEEP),
	/* H4  : I2C0_SDA ==> PCH_I2C_AUD_SDA */
	PAD_CFG_NF(GPP_H4, NONE, DEEP, NF1),
	/* H5  : I2C0_SCL ==> PCH_I2C_AUD_SCL */
	PAD_CFG_NF(GPP_H5, NONE, DEEP, NF1),
	/* H6  : I2C1_SDA ==> PCH_I2C_TCHSCR_SDA */
	PAD_CFG_NF(GPP_H6, NONE, DEEP, NF1),
	/* H7  : I2C1_SCL ==> PCH_I2C_TCHSCR_SCL */
	PAD_CFG_NF(GPP_H7, NONE, DEEP, NF1),
	/* H8  : I2C4_SDA ==> WWAN_WLAN_COEX1 */
	PAD_CFG_NF(GPP_H8, NONE, DEEP, NF2),
	/* H9  : I2C4_SCL ==> WWAN_WLAN_COEX2 */
	PAD_CFG_NF(GPP_H9, NONE, DEEP, NF2),
	/* H10 : UART0_RXD ==> UART_PCH_RX_DBG_TX */
	PAD_CFG_NF(GPP_H10, NONE, DEEP, NF2),
	/* H11 : UART0_TXD ==> UART_PCH_TX_DBG_RX */
	PAD_CFG_NF(GPP_H11, NONE, DEEP, NF2),
	/* H12 : I2C7_SDA ==> SD_PE_WAKE_ODL */
	PAD_CFG_GPI(GPP_H12, NONE, DEEP),
	/* H13 : I2C7_SCL ==> EN_PP3300_SD */
	PAD_NC(GPP_H13, UP_20K),
	/* H14 : NC */
	PAD_NC(GPP_H14, NONE),
	/* H15 : DDPB_CTRLCLK ==> DDIB_HDMI_CTRLCLK */
	PAD_CFG_NF(GPP_H15, NONE, DEEP, NF1),
	/* H16 : NC */
	PAD_NC(GPP_H16, NONE),
	/* H17 : DDPB_CTRLDATA ==> DDIB_HDMI_CTRLDATA */
	PAD_CFG_NF(GPP_H17, NONE, DEEP, NF1),
	/* H18 : PROC_C10_GATE# ==> CPU_C10_GATE_L */
	PAD_CFG_NF(GPP_H18, NONE, DEEP, NF1),
	/* H19 : SRCCLKREQ4# ==> SAR1_INT_L */
	PAD_CFG_GPI_APIC(GPP_H19, NONE, PLTRST, LEVEL, NONE),
	/* H20 : IMGCLKOUT1 ==> WLAN_PERST_L */
	PAD_CFG_GPO(GPP_H20, 1, DEEP),
	/* H21 : IMGCLKOUT2 ==>  UCAM_MCLK */
	PAD_CFG_GPO(GPP_H21, 0, DEEP),
	/* H22 : IMGCLKOUT3 ==> WCAM_MCLK_R */
	PAD_CFG_NF(GPP_H22, NONE, DEEP, NF1),
	/* H23 : SRCCLKREQ5# ==> WWAN_CLKREQ_ODL */
	PAD_CFG_NF(GPP_H23, NONE, DEEP, NF2),

	/* R0 : HDA_BCLK ==> I2S_HP_SCLK_R */
	PAD_CFG_NF(GPP_R0, NONE, DEEP, NF2),
	/* R1 : HDA_SYNC ==> I2S_HP_SFRM_R */
	PAD_CFG_NF(GPP_R1, NONE, DEEP, NF2),
	/* R2 : HDA_SDO ==> I2S_PCH_TX_HP_RX_STRAP */
	PAD_CFG_NF(GPP_R2, DN_20K, DEEP, NF2),
	/* R3 : HDA_SDIO ==> I2S_PCH_RX_HP_TX */
	PAD_CFG_NF(GPP_R3, NONE, DEEP, NF2),
	/* R4 : HDA_RST# ==> I2S_SPKR_SCLK_R */
	PAD_CFG_NF(GPP_R4, NONE, DEEP, NF2),
	/* R5 : HDA_SDI1 ==> I2S_SPKR_SFRM_R */
	PAD_CFG_NF(GPP_R5, NONE, DEEP, NF2),
	/* R6 : I2S2_TXD ==> I2S_PCH_TX_SPKR_RX_R */
	PAD_CFG_NF(GPP_R6, NONE, DEEP, NF2),
	/* R7 : I2S2_RXD ==> I2S_PCH_RX_SPKR_TX */
	PAD_CFG_NF(GPP_R7, NONE, DEEP, NF2),

	/* S0 : SNDW0_CLK ==> SDW_HP_CLK_R */
	PAD_CFG_NF(GPP_S0, NONE, DEEP, NF1),
	/* S1 : SNDW0_DATA ==> SDW_HP_DATA_R */
	PAD_CFG_NF(GPP_S1, NONE, DEEP, NF1),
	/* S2 : SNDW1_CLK ==> DMIC_CLK0_R */
	PAD_CFG_NF(GPP_S2, NONE, DEEP, NF2),
	/* S3 : SNDW1_DATA ==> DMIC_DATA0_R */
	PAD_CFG_NF(GPP_S3, NONE, DEEP, NF2),
	/* S4 : SNDW2_CLK ==> SDW_SPKR_CLK */
	PAD_CFG_NF(GPP_S4, NONE, DEEP, NF1),
	/* S5 : SNDW2_DATA ==> SDW_SPKR_DATA */
	PAD_CFG_NF(GPP_S5, NONE, DEEP, NF1),
	/* S6 : SNDW3_CLK ==> DMIC_CLK1_R */
	PAD_CFG_NF(GPP_S6, NONE, DEEP, NF2),
	/* S7 : SNDW3_DATA ==> DMIC_DATA1_R */
	PAD_CFG_NF(GPP_S7, NONE, DEEP, NF2),

	/* GPD0: BATLOW# ==> BATLOW_L */
	PAD_CFG_NF(GPD0, NONE, DEEP, NF1),
	/* GPD1: ACPRESENT ==> PCH_ACPRESENT */
	PAD_CFG_NF(GPD1, NONE, DEEP, NF1),
	/* GPD2 : LAN_WAKE# ==> EC_PCH_WAKE_ODL */
	PAD_CFG_NF(GPD2, NONE, DEEP, NF1),
	/* GPD3: PWRBTN# ==> EC_PCH_PWR_BTN_ODL */
	PAD_CFG_NF(GPD3, NONE, DEEP, NF1),
	/* GPD4: SLP_S3# ==> SLP_S3_L */
	PAD_CFG_NF(GPD4, NONE, DEEP, NF1),
	/* GPD5: SLP_S4# ==> SLP_S4_L */
	PAD_CFG_NF(GPD5, NONE, DEEP, NF1),
	/* GPD6: SLP_A# ==> SLP_A_L */
	PAD_CFG_NF(GPD6, NONE, DEEP, NF1),
	/* GPD7: GPD7_STRAP */
	PAD_NC(GPD7, NONE),
	/* GPD8: SUSCLK ==> PCH_SUSCLK */
	PAD_CFG_NF(GPD8, NONE, DEEP, NF1),
	/* GPD9: SLP_WLAN# ==> SLP_WLAN_L */
	PAD_CFG_NF(GPD9, NONE, DEEP, NF1),
	/* GPD10: SLP_S5# ==> SLP_S5_L */
	PAD_CFG_NF(GPD10, NONE, DEEP, NF1),
	/* GPD11: LANPHYC ==> WWAN_CONFIG1 */
	PAD_CFG_GPI(GPD11, NONE, DEEP),

	/* Virtual GPIO */
	/* Put unused Cnvi BT UART lines in NC mode since we use USB mode. */
	PAD_NC(GPP_VGPIO_6, NONE),
	PAD_NC(GPP_VGPIO_7, NONE),
	PAD_NC(GPP_VGPIO_8, NONE),
	PAD_NC(GPP_VGPIO_9, NONE),

	/* Put unused Cnvi UART0 lines in NC mode since we use USB mode. */
	PAD_NC(GPP_VGPIO_18, NONE),
	PAD_NC(GPP_VGPIO_19, NONE),
	PAD_NC(GPP_VGPIO_20, NONE),
	PAD_NC(GPP_VGPIO_21, NONE),
};

/* Early pad configuration in bootblock */
static const struct pad_config early_gpio_table[] = {
	/* A12 : SATAXPCIE1 ==> EN_PPVAR_WWAN */
	PAD_CFG_GPO(GPP_A12, 1, DEEP),
	/* A13 : PMC_I2C_SCL ==> GSC_PCH_INT_ODL */
	PAD_CFG_GPI_APIC(GPP_A13, NONE, PLTRST, LEVEL, INVERT),
	/* B4  : PROC_GP3 ==> SSD_PERST_L */
	PAD_CFG_GPO(GPP_B4, 0, DEEP),
	/* B7  : ISH_12C1_SDA ==> PCH_I2C_TPM_SDA */
	PAD_CFG_NF(GPP_B7, NONE, DEEP, NF2),
	/* B8  : ISH_12C1_SCL ==> PCH_I2C_TPM_SCL */
	PAD_CFG_NF(GPP_B8, NONE, DEEP, NF2),
	/*
	 * D1  : ISH_GP1 ==> FP_RST_ODL
	 * FP_RST_ODL comes out of reset as hi-z and does not have an external pull-down.
	 * To ensure proper power sequencing for the FPMCU device, reset signal is driven low
	 * early on in bootblock, followed by enabling of power. Reset signal is deasserted
	 * later on in ramstage. Since reset signal is asserted in bootblock, it results in
	 * FPMCU not working after a S3 resume. This is a known issue.
	 */
	PAD_CFG_GPO(GPP_D1, 0, DEEP),
	/* D2  : ISH_GP2 ==> EN_FP_PWR */
	PAD_CFG_GPO(GPP_D2, 1, DEEP),
	/* E13 : THC0_SPI1_IO2 ==> MEM_CH_SEL */
	PAD_CFG_GPI(GPP_E13, NONE, DEEP),
	/* E16 : RSVD_TP ==> WWAN_RST_L
	 * To meet timing constrains - drive reset low.
	 * Deasserted in ramstage.
	 */
	PAD_CFG_GPO(GPP_E16, 0, DEEP),
	/* E15 : RSVD_TP ==> PCH_WP_OD */
	PAD_CFG_GPI_GPIO_DRIVER(GPP_E15, NONE, DEEP),
	/* H10 : UART0_RXD ==> UART_PCH_RX_DBG_TX */
	PAD_CFG_NF(GPP_H10, NONE, DEEP, NF2),
	/* H11 : UART0_TXD ==> UART_PCH_TX_DBG_RX */
	PAD_CFG_NF(GPP_H11, NONE, DEEP, NF2),
	/* H13 : I2C7_SCL ==> EN_PP3300_SD */
	PAD_NC(GPP_H13, UP_20K),
};

const struct pad_config *__weak variant_gpio_table(size_t *num)
{
	*num = ARRAY_SIZE(gpio_table);
	return gpio_table;
}

const struct pad_config *__weak variant_gpio_override_table(size_t *num)
{
	*num = 0;
	return NULL;
}

const struct pad_config *__weak variant_early_gpio_table(size_t *num)
{
	*num = ARRAY_SIZE(early_gpio_table);
	return early_gpio_table;
}

static const struct cros_gpio cros_gpios[] = {
	CROS_GPIO_REC_AL(CROS_GPIO_VIRTUAL, CROS_GPIO_DEVICE_NAME),
	CROS_GPIO_WP_AH(GPIO_PCH_WP, CROS_GPIO_DEVICE_NAME),
};

const struct cros_gpio *__weak variant_cros_gpios(size_t *num)
{
	*num = ARRAY_SIZE(cros_gpios);
	return cros_gpios;
}

const struct pad_config *__weak variant_romstage_gpio_table(size_t *num)
{
	*num = 0;
	return NULL;
}
