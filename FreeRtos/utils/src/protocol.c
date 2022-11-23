/*****************************************************************
 * name:	prptocol.c
 * function:	协议解析
 * author:	sxh
 * date:	2022-11-23
 * version:	1.0.0
  -------------------------------------------------------------------------
 |  帧头 | 数据长度 | 指令码  | 读写标志位 | 数据 | 校验和的低八位| 帧尾   |
 |________________________________________________________________
 | 0x5A  |     n    |   code  |   0/1      | data |      crc_l    | 0xA5   |
 |__________________________________________________________________________
  n = 4+ndata   crc = 数据长度+指令码+读写标志位+ndata
*****************************************************************/

#include "stdio.h"
#include "stdint.h"



////接收数据按协议解码,info:协议状态,dat:新接收的数据
//bool RecvDataDecode(recv_info_t *info,uint8_t dat)
//{

//	bool result = FALSE;
//	
//	if(KEYWORD == info->last_data)
//	{
//		if(STX != dat
//			&& ETX != dat
//			&& KEYWORD != dat)
//		{
//			info->stat = E_RECV_STAT_INIT;
//			return FALSE;
//		}
//		info->last_data = 0;
//	}
//	else if(KEYWORD == dat)
//	{
//		info->last_data = dat;
//		return FALSE;
//	}
//	else if(STX == dat)
//	{
//		info->stat = E_RECV_STAT_INIT;
//		info->last_data = 0;
//	}
//	else
//		info->last_data = dat;

//	switch(info->stat)
//	{
//	case E_RECV_STAT_INIT:
//		if(dat == STX)
//		{
//			info->stat++;
//			info->id = 0;
//		}
//		info->index = 0;
//		break;
//		
//	case E_RECV_STAT_ID:
//		info->id += dat << (8 * info->index);
//		info->index++;
//		if(info->index >= 4)
//		{
//			info->len = 0;
//			info->index = 0;
//			info->stat++;
//		}
//		break;
//		
//	case E_RECV_STAT_LEN:
//		info->len += dat << (8 * info->index);
//		info->index++;
//		if(info->index >= 2)
//		{
//			info->index = 0;
//			info->cmd = 0;
//			if(info->len < 4)
//			{
//				info->stat = E_RECV_STAT_INIT;
//				break;
//			}
//			info->len -= 4;
//			
//			if(info->len > MAX_RECV_DATA)
//			{
//				info->stat = E_RECV_STAT_INIT;
//				break;
//			}
//			info->stat++;
//		}
//		break;
//	case E_RECV_STAT_CMD:
//		info->cmd += dat << (8 * info->index);
//		info->index++;
//		if(info->index >= 2)
//		{
//			info->index = 0;
//			info->error = 0;
//			info->stat++;
//		}	
//		break;
//		
//	case E_RECV_STAT_ERR:
//		info->error += dat << (8 * info->index);
//		info->index++;
//		if(info->index >= 2)
//		{
//			info->index = 0;
//			if(info->len == 0)
//			{
//				info->stat = E_RECV_STAT_END;
//			}
//			else
//			{
//				info->stat++;
//			}
//		}	
//		break;
//		
//	case E_RECV_STAT_DAT:
//		info->buff[info->index] = dat;
//		info->index++;
//		if(info->index >= info->len)
//		{
//			info->stat++;
//			info->index = 0;
//		}
//		break;
//		
//	case E_RECV_STAT_END:
//		if(ETX == dat)
//		{
//			result = TRUE;
//		}
//		info->index = 0;		
//		info->stat = E_RECV_STAT_INIT;
//		break;
//		
//	default:
//		info->index = 0;		
//		info->stat = E_RECV_STAT_INIT;
//		break;
//	}
//	return result;
//}


//void Uart_proc(void)
//{
//	uint8_t dat;
//	uint8_t err;
//	bool isRet;
//	recv_info_t *info = & recvInfo;
//	
//	while(Buff8Read(&recvBuff, &dat))
//	{
//		if(RecvDataDecode(info,dat))
//		{
//			isRet = TRUE;
//			err = E_ERR_NONE;
//			switch (info->cmd)
//			{
//			case E_CMD_WR_CFG:
//				if(sizeof(radar_config_t) == info->len)
//				{
//					radar_config_t *cfg = (radar_config_t *)info->buff;

//					if(cfg->GateLen < GATE_LEN_MIN || cfg->GateLen > GATE_LEN_MAX)
//					{
//						err = E_ERR_PARA_ERR;
//					}
//					else if(cfg->SenLevel < SEN_LEVEL_MIN)
//					{
//						err = E_ERR_PARA_ERR;
//					}
//					else if(cfg->Threshold < THRESHOLD_MIN)
//					{
//						err = E_ERR_PARA_ERR;
//					}
//					else if(cfg->CloseTime > GATE_CLOSE_TIME_MAX )
//					{
//						err = E_ERR_PARA_ERR;
//					}
//					else if(cfg->CarDlyTime > CAR_DELAY_TIME)
//					{
//						err = E_ERR_PARA_ERR;
//					}
//					else if(cfg->CarMinTime > CAR_MIN_TIME)
//					{
//						err = E_ERR_PARA_ERR;
//					}
//					else
//					{	//保存参数
//						radar_config_t *radar = GetConfig();
//						if(my_memcmp(radar,cfg,sizeof(radar_config_t)))
//						{
//							my_memcpy(radar,cfg,sizeof(radar_config_t),sizeof(radar_config_t));
//							Save_config(cfg);
//						}
//					}
//				}
//				else
//				{
//					err = E_ERR_LEN_ERR;
//				}
//				info->len = 0;
//				break;
//			case E_CMD_RD_CFG:
//				{
//					radar_config_t *radar = (radar_config_t *)info->buff;
//					radar_config_t *cfg = GetConfig();
//					my_memcpy(radar,cfg,sizeof(radar_config_t),sizeof(radar_config_t));
//					info->len = sizeof(radar_config_t);
//				}
//				break;
//			case E_CMD_ENTER_ADMIN:
//				AdminTime100msCnt = 50;	//5s
//				info->len = 0;
//				isRet = FALSE;
//				break;
//			case E_CMD_EXIT_ADMIN:
//				info->len = 0;
//				break;
//			case E_CMD_GET_VERSION:
//				dat = my_strlen(VERSION_CUST);
//				info->len = my_memcpy(info->buff, VERSION_CUST, dat,MAX_RECV_DATA);
//				dat = my_strlen(" Buid:");
//				info->len += my_memcpy(info->buff+info->len, " Buid:", dat,MAX_RECV_DATA-info->len);
//				dat = my_strlen(__DATE__);
//				info->len += my_memcpy(info->buff+info->len, __DATE__, dat,MAX_RECV_DATA-info->len);
//				break;
//			case E_CMD_RESET:
//				info->len = 0;
//				SendDataEncode(info->cmd,err,info->buff,info->len);	
//				RunCount(10);
//				while(!IsTimeUp());
//				NVIC_SystemReset();
//				break;
//			case E_CMD_RESET_CONGIG:
//				Config_reset();
//				{
//				radar_config_t *radar = (radar_config_t *)info->buff;
//				radar_config_t *cfg = GetConfig();
//				my_memcpy(radar,cfg,sizeof(radar_config_t),sizeof(radar_config_t));
//				info->len = sizeof(radar_config_t);
//				}	
//				break;
//			case E_CMD_UPDATE:
//			    /* Enable PMU and BKPI clock */
//			  rcu_periph_clock_enable(RCU_PMU);
//			  rcu_periph_clock_enable(RCU_BKPI);
//				/* Enable wrcu_periph_clock_enablerite access to Backup domain */
//				pmu_backup_write_enable();

//				/* Clear Tamper pin Event(TE) pending flag */
//				bkp_flag_clear();
//				
//			  bkp_data_write(BKP_DATA_0,UPDATE_FLAG);
//				info->len = 0;
//				SendDataEncode(info->cmd,err,info->buff,info->len);	
//				RunCount(10);
//				while(!IsTimeUp());
//				NVIC_SystemReset();
//				break;
//				
//			case E_CMD_GET_KEY:
//				info->len = GetAESKeys((uint32_t *)info->buff);
//				info->len *= 4;
//				isRet = TRUE;
//				break;
//				
//			case E_CMD_SET_KEY:
//				if(info->len == 20)
//				{
//					info->error=WriteAESKeys((uint32_t *)info->buff);
//				}
//				else
//				{
//					info->error = E_ERR_LEN_ERR;
//				}
//				info->len = 0;
//				isRet = TRUE;
//				break;
//				
//			case E_CMD_LOCK:
//				fmc_unlock();
//				ob_security_protection_config(FMC_USPC);
//				fmc_lock();
//				info->len = 0;
//				isRet = TRUE;
//				break;
//			case E_CMD_UNLOCK:
//				fmc_unlock();
//				ob_security_protection_config(FMC_NSPC);
//				fmc_lock();
//				info->len = 0;
//				isRet = TRUE;
//				break;
//			default:
//				err = E_ERR_UNKOWN_CMD;
//				info->len = 0;
//				break;
//			}
//			if(isRet)
//			{
//				SendDataEncode(info->cmd,err,info->buff,info->len);
//			}
//		}
//	}
//}
