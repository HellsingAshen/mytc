drop sequence ATTACHED_FILE_INFO_SEQ;
drop sequence CFG_CONFIGSERVER_PARAM_SEQ;
drop sequence CFG_TRANS_ACCESS_SEQ;
drop sequence CFG_TRANS_INFO_SEQ;
drop sequence CONSUL_ENVINFO_SEQ;
drop sequence DEMAND_INFO_SEQ;
drop sequence ENVIRONMENT_INFO_SERVICE_SEQ;
drop sequence ENVIRONMENT_INFO_TRANS_SEQ;
drop sequence ENV_CONFIG_SEQ;
drop sequence MESSAGE_CODEC_INFO_SEQ;
drop sequence MICRO_SERVICE_ENVINFO_SEQ;
drop sequence PROTOCOL_CODEC_INFO_SEQ;
drop sequence PROTOCOL_CONFIG_SEQ;
drop sequence SCP_SERVICE_LOG_SEQ;
drop sequence SCP_TRANS_LOG_SEQ;
drop sequence SERVICE_DEFINE_SEQ;
drop sequence SERVICE_ENV_REL_SEQ;
drop sequence SERVICE_INFO_SEQ;
drop sequence STAGE_INFO_SEQ;
drop sequence SYSTEM_INFO_SEQ;
drop sequence TRANS_CONTENT_SEQ;
drop sequence TRANS_DEFINE_INFO_SEQ;
drop sequence TRANS_ENV_REL_SEQ;
drop sequence USER_INFO_SEQ;
drop sequence ROLE_INFO_SEQ;
drop sequence MEUN_SEQ;

CREATE SEQUENCE ATTACHED_FILE_INFO_SEQ AS BIGINT START WITH 1 INCREMENT BY 1 NO MAXVALUE CACHE 10 CYCLE ORDER;
CREATE SEQUENCE CFG_CONFIGSERVER_PARAM_SEQ AS BIGINT START WITH 1 INCREMENT BY 1 NO MAXVALUE CACHE 10 CYCLE ORDER;
CREATE SEQUENCE CFG_TRANS_ACCESS_SEQ AS BIGINT START WITH 1 INCREMENT BY 1 NO MAXVALUE CACHE 10 CYCLE ORDER;
CREATE SEQUENCE CFG_TRANS_INFO_SEQ AS BIGINT START WITH 1 INCREMENT BY 1 NO MAXVALUE CACHE 10 CYCLE ORDER;
CREATE SEQUENCE CONSUL_ENVINFO_SEQ AS BIGINT START WITH 1 INCREMENT BY 1 NO MAXVALUE CACHE 10 CYCLE ORDER;
CREATE SEQUENCE DEMAND_INFO_SEQ AS BIGINT START WITH 1 INCREMENT BY 1 NO MAXVALUE CACHE 10 CYCLE ORDER;
CREATE SEQUENCE ENVIRONMENT_INFO_SERVICE_SEQ AS BIGINT START WITH 1 INCREMENT BY 1 NO MAXVALUE CACHE 10 CYCLE ORDER;
CREATE SEQUENCE ENVIRONMENT_INFO_TRANS_SEQ AS BIGINT START WITH 1 INCREMENT BY 1 NO MAXVALUE CACHE 10 CYCLE ORDER;
CREATE SEQUENCE ENV_CONFIG_SEQ AS BIGINT START WITH 1 INCREMENT BY 1 NO MAXVALUE CACHE 10 CYCLE ORDER;
CREATE SEQUENCE MESSAGE_CODEC_INFO_SEQ AS BIGINT START WITH 1 INCREMENT BY 1 NO MAXVALUE CACHE 10 CYCLE ORDER;
CREATE SEQUENCE MICRO_SERVICE_ENVINFO_SEQ AS BIGINT START WITH 1 INCREMENT BY 1 NO MAXVALUE CACHE 10 CYCLE ORDER;
CREATE SEQUENCE PROTOCOL_CODEC_INFO_SEQ AS BIGINT START WITH 1 INCREMENT BY 1 NO MAXVALUE CACHE 10 CYCLE ORDER;
CREATE SEQUENCE PROTOCOL_CONFIG_SEQ AS BIGINT START WITH 1 INCREMENT BY 1 NO MAXVALUE CACHE 10 CYCLE ORDER;
CREATE SEQUENCE SCP_SERVICE_LOG_SEQ AS BIGINT START WITH 1 INCREMENT BY 1 NO MAXVALUE CACHE 10 CYCLE ORDER;
CREATE SEQUENCE SCP_TRANS_LOG_SEQ AS BIGINT START WITH 1 INCREMENT BY 1 NO MAXVALUE CACHE 10 CYCLE ORDER;
CREATE SEQUENCE SERVICE_DEFINE_SEQ AS BIGINT START WITH 1 INCREMENT BY 1 NO MAXVALUE CACHE 10 CYCLE ORDER;
CREATE SEQUENCE SERVICE_ENV_REL_SEQ AS BIGINT START WITH 1 INCREMENT BY 1 NO MAXVALUE CACHE 10 CYCLE ORDER;
CREATE SEQUENCE SERVICE_INFO_SEQ AS BIGINT START WITH 1 INCREMENT BY 1 NO MAXVALUE CACHE 10 CYCLE ORDER;
CREATE SEQUENCE SYSTEM_INFO_SEQ AS BIGINT START WITH 200000 INCREMENT BY 1 NO MAXVALUE CACHE 10 CYCLE ORDER;
CREATE SEQUENCE STAGE_INFO_SEQ AS BIGINT START WITH 1 INCREMENT BY 1 NO MAXVALUE CACHE 10 CYCLE ORDER;
CREATE SEQUENCE TRANS_CONTENT_SEQ AS BIGINT START WITH 1 INCREMENT BY 1 NO MAXVALUE CACHE 10 CYCLE ORDER;
CREATE SEQUENCE TRANS_DEFINE_INFO_SEQ AS BIGINT START WITH 1 INCREMENT BY 1 NO MAXVALUE CACHE 10 CYCLE ORDER;
CREATE SEQUENCE TRANS_ENV_REL_SEQ AS BIGINT START WITH 1 INCREMENT BY 1 NO MAXVALUE CACHE 10 CYCLE ORDER;
CREATE SEQUENCE USER_INFO_SEQ AS BIGINT START WITH 1 INCREMENT BY 1 NO MAXVALUE CACHE 10 CYCLE ORDER;
CREATE SEQUENCE ROLE_INFO_SEQ AS BIGINT START WITH 1 INCREMENT BY 1 NO MAXVALUE CACHE 10 CYCLE ORDER;
CREATE SEQUENCE MEUN_SEQ AS BIGINT START WITH 1 INCREMENT BY 1 NO MAXVALUE CACHE 10 CYCLE ORDER;
