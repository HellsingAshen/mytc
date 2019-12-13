-- ----------------------------
-- Table structure for attached_file_info
-- ----------------------------
DROP TABLE attached_file_info;
CREATE TABLE attached_file_info (
  ID int NOT NULL,
  DEMAND_ID varchar(11) DEFAULT NULL,
  PATH varchar(300) DEFAULT NULL,
  PRIMARY KEY (ID)
);

-- ----------------------------
-- Records of attached_file_info
-- ----------------------------

-- ----------------------------
-- Table structure for cfg_configserver_param
-- ----------------------------
DROP TABLE cfg_configserver_param;
CREATE TABLE cfg_configserver_param (
  ID int NOT NULL,
  CONFIG_KEY varchar(300) DEFAULT NULL,
  CONFIG_VALUE varchar(500) DEFAULT NULL,
  APPLICATION varchar(200) DEFAULT NULL,
  PROFILE varchar(200) DEFAULT NULL,
  LABEL varchar(200) DEFAULT NULL,
  STATUS varchar(1) DEFAULT NULL,
  CREATE_USER varchar(100) DEFAULT NULL,
  CREATE_DATE timestamp NULL DEFAULT NULL,
  UPDATE_USER varchar(100) DEFAULT NULL,
  UPDATE_DATE timestamp NULL DEFAULT NULL,
  CONFIG_VALUE_NAME varchar(200) DEFAULT NULL,
  PRIMARY KEY (ID)
);

-- ----------------------------
-- Records of cfg_configserver_param
-- ----------------------------
INSERT INTO cfg_configserver_param VALUES ('1', 'netty.threadSize', '3', 'scp-gateway', 'dev', 'dev', '1', null, '2019-11-07 15:11:34', null, '2019-11-07 15:11:48', '111');
INSERT INTO cfg_configserver_param VALUES ('3', 'async.executor.thread.max_pool_size', '50', 'scp-public', 'dev', 'dev', '1', null, null, null, null, null);
INSERT INTO cfg_configserver_param VALUES ('4', 'async.executor.thread.queue_capacity', '99999', 'scp-public', 'dev', 'dev', '1', null, null, null, null, null);
INSERT INTO cfg_configserver_param VALUES ('5', 'async.executor.thread.name.prefix', 'async-service-', 'scp-gateway', 'dev', 'dev', '1', null, null, null, null, null);
INSERT INTO cfg_configserver_param VALUES ('6', 'spring.rabbitmq.host', '10.0.160.201', 'scp-public', 'dev', 'dev', '1', null, '2019-11-07 22:48:12', null, '2019-11-07 22:48:12', null);
INSERT INTO cfg_configserver_param VALUES ('7', 'spring.rabbitmq.port', '5672', 'scp-public', 'dev', 'dev', '1', null, '2019-11-07 22:48:13', null, '2019-11-07 22:48:13', null);
INSERT INTO cfg_configserver_param VALUES ('8', 'spring.rabbitmq.username', 'scp', 'scp-public', 'dev', 'dev', '1', null, '2019-11-07 22:48:14', null, '2019-11-07 22:48:14', null);
INSERT INTO cfg_configserver_param VALUES ('9', 'spring.rabbitmq.password', 'scp', 'scp-public', 'dev', 'dev', '1', null, '2019-11-07 22:48:15', null, '2019-11-07 22:48:15', null);
INSERT INTO cfg_configserver_param VALUES ('10', 'spring.rabbitmq.virtual-host', '/', 'scp-public', 'dev', 'dev', '1', null, '2019-11-07 22:48:28', null, '2019-11-07 22:48:28', null);
INSERT INTO cfg_configserver_param VALUES ('11', 'spring.rule.rabbitmq.queue.name', 'scpFlowRule', 'scp-gateway', 'dev', 'dev', '1', null, null, null, null, null);
INSERT INTO cfg_configserver_param VALUES ('33', 'spring.cloud.sentinel.transport.port', '8719', 'scp-gateway', 'dev', 'dev', '1', null, null, null, null, null);
INSERT INTO cfg_configserver_param VALUES ('34', 'spring.cloud.sentinel.transport.dashboard', '127.0.0.1:8080', 'scp-gateway', 'dev', 'dev', '1', null, null, null, null, null);
INSERT INTO cfg_configserver_param VALUES ('35', 'spring.cloud.sentinel.eager', 'true', 'scp-gateway', 'dev', 'dev', '1', null, null, null, null, null);
INSERT INTO cfg_configserver_param VALUES ('36', 'spring.cloud.consul.host', '127.0.0.1', 'scp-public', 'dev', 'dev', '1', null, '2019-11-08 07:26:40', null, '2019-11-08 07:26:40', null);
INSERT INTO cfg_configserver_param VALUES ('37', 'spring.cloud.consul.port', '8500', 'scp-public', 'dev', 'dev', '1', null, '2019-11-08 07:26:46', null, '2019-11-08 07:26:46', null);
INSERT INTO cfg_configserver_param VALUES ('38', 'consul.services.path', null, 'scp-gateway', 'dev', 'dev', '1', null, null, null, null, null);
INSERT INTO cfg_configserver_param VALUES ('39', 'remoteFlag', 'true', 'scp-gateway', 'dev', 'dev', '1', null, null, null, null, null);
INSERT INTO cfg_configserver_param VALUES ('40', 'db.name', 'root', 'scp-public', 'dev', 'dev', '1', null, null, null, null, null);
INSERT INTO cfg_configserver_param VALUES ('41', 'db.password', 'root', 'scp-public', 'dev', 'dev', '1', null, null, null, null, null);
INSERT INTO cfg_configserver_param VALUES ('42', 'db.driver', 'com.mysql.jdbc.Driver', 'scp-public', 'dev', 'dev', '1', null, null, null, null, null);
INSERT INTO cfg_configserver_param VALUES ('43', 'db.url', 'jdbc:mysql://127.0.0.1:3306/scptest?characterEncoding=utf8&useSSL=false&serverTimezone=UTC&rewriteBatchedStatements=true', 'scp-public', 'dev', 'dev', '1', null, null, null, null, null);
INSERT INTO cfg_configserver_param VALUES ('44', 'flow.lever', '1', 'scp-gateway', 'dev', 'dev', '1', null, null, null, null, null);
INSERT INTO cfg_configserver_param VALUES ('45', 'async.executor.thread.core_pool_size', '20', 'scp-public', 'dev', 'dev', '1', null, null, null, null, null);
INSERT INTO cfg_configserver_param VALUES ('46', 'async.executor.thread.name.prefix', 'async-service-main-', 'scp-main', 'dev', 'dev', '1', null, null, null, null, null);
INSERT INTO cfg_configserver_param VALUES ('47', 'tomcat.maxConnectSize', '20000', 'scp-public', 'dev', 'dev', '1', null, '2019-11-08 11:29:10', null, '2019-11-08 11:29:10', null);
INSERT INTO cfg_configserver_param VALUES ('48', 'tomcat.maxThreadSize', '2000', 'scp-public', 'dev', 'dev', '1', null, '2019-11-08 11:29:11', null, '2019-11-08 11:29:11', null);
INSERT INTO cfg_configserver_param VALUES ('49', 'tomcat.connectTimeOut', '30000', 'scp-public', 'dev', 'dev', '1', null, '2019-11-08 11:29:13', null, '2019-11-08 11:29:13', null);
INSERT INTO cfg_configserver_param VALUES ('50', 'netty.threadSize', '4', 'scp-main', 'dev', 'dev', '1', null, null, null, null, null);
INSERT INTO cfg_configserver_param VALUES ('51', 'spring.rabbitmq.host', '10.0.160.201', 'scp-log', 'dev', 'dev', '1', null, '2019-11-07 22:49:01', null, '2019-11-07 22:49:01', null);
INSERT INTO cfg_configserver_param VALUES ('52', 'spring.rabbitmq.rabbitConsumers', '1', 'scp-public', 'dev', 'dev', '1', null, '2019-11-07 23:03:04', null, '2019-11-07 23:03:04', null);
INSERT INTO cfg_configserver_param VALUES ('53', 'spring.rabbitmq.maxRabbitConsumers', '20', 'scp-public', 'dev', 'dev', '1', null, '2019-11-07 23:04:39', null, '2019-11-07 23:04:39', null);
INSERT INTO cfg_configserver_param VALUES ('54', 'spring.rabbitmq.port', '5672', 'scp-log', 'dev', 'dev', '1', null, '2019-11-07 22:48:54', null, '2019-11-07 22:48:54', null);
INSERT INTO cfg_configserver_param VALUES ('55', 'spring.rabbitmq.virtualHost', '/', 'scp-log', 'dev', 'dev', '1', null, '2019-11-07 22:48:52', null, '2019-11-07 22:48:52', null);
INSERT INTO cfg_configserver_param VALUES ('56', 'spring.rabbitmq.queue.trans', 'scpTransLog', 'scp-public', 'dev', 'dev', '1', null, '2019-11-08 08:34:37', null, '2019-11-08 08:34:37', null);
INSERT INTO cfg_configserver_param VALUES ('57', 'spring.rabbitmq.queue.service', 'scpServiceLog', 'scp-public', 'dev', 'dev', '1', null, '2019-11-08 08:35:42', null, '2019-11-08 08:35:42', null);
INSERT INTO cfg_configserver_param VALUES ('58', 'transIdKey', 'transId', 'scp-public', 'dev', 'dev', '1', null, '2019-11-08 08:26:59', null, '2019-11-08 08:26:59', null);
INSERT INTO cfg_configserver_param VALUES ('59', 'sysIdKey', 'sysId', 'scp-public', 'dev', 'dev', '1', null, '2019-11-08 08:27:04', null, '2019-11-08 08:27:04', null);
INSERT INTO cfg_configserver_param VALUES ('60', 'logHandlerFlag', 'true', 'scp-public', 'dev', 'dev', '1', null, '2019-11-08 08:27:05', null, '2019-11-08 08:27:05', null);

-- ----------------------------
-- Table structure for cfg_degraderule_define
-- ----------------------------
DROP TABLE cfg_degraderule_define;
CREATE TABLE cfg_degraderule_define (
  R_id varchar(32) NOT NULL,
  R_resource varchar(200) NOT NULL,
  r_count varchar(20) NOT NULL,
  R_grade varchar(10) DEFAULT NULL,
  r_timeWindow varchar(11) DEFAULT NULL,
  status varchar(2) DEFAULT NULL,
  create_User varchar(200) DEFAULT NULL,
  create_Date timestamp NULL DEFAULT NULL,
  update_User varchar(200) DEFAULT NULL,
  update_Date timestamp NULL DEFAULT NULL,
  PRIMARY KEY (R_id)
);

-- ----------------------------
-- Records of cfg_degraderule_define
-- ----------------------------

-- ----------------------------
-- Table structure for cfg_flowcontrolrule_define
-- ----------------------------
DROP TABLE cfg_flowcontrolrule_define;
CREATE TABLE cfg_flowcontrolrule_define (
  r_id varchar(32) NOT NULL,
  r_resource varchar(200) NOT NULL,
  r_count varchar(20) DEFAULT NULL,
  r_grade varchar(32) DEFAULT NULL,
  r_limitApp varchar(32) DEFAULT NULL,
  r_strategy varchar(10) DEFAULT NULL,
  r_controlBehavior varchar(10) DEFAULT NULL,
  r_isCluster varchar(10) DEFAULT NULL,
  status varchar(2) DEFAULT NULL,
  create_User varchar(200) DEFAULT NULL,
  create_Date timestamp DEFAULT NULL,
  update_user varchar(200) DEFAULT NULL,
  update_Date timestamp DEFAULT NULL,
  PRIMARY KEY (r_id)
);

-- ----------------------------
-- Records of cfg_flowcontrolrule_define
-- ----------------------------

-- ----------------------------
-- Table structure for cfg_flow_define
-- ----------------------------
DROP TABLE cfg_flow_define;
CREATE TABLE cfg_flow_define (
  FLOW_ID varchar(8) NOT NULL,
  TRANS_ID int NOT NULL,
  SERVICE_ID int DEFAULT NULL,
  DEPEND varchar(128) DEFAULT NULL,
  PROC_BEFORE varchar(16) DEFAULT NULL,
  PROC_AFTER varchar(16) DEFAULT NULL,
  NODE_TYPE char(1) DEFAULT NULL,
  CREATE_BY varchar(32) DEFAULT NULL,
  CREATE_DATE timestamp DEFAULT NULL,
  UPDATE_BY varchar(32) DEFAULT NULL,
  UPDATE_DATE timestamp DEFAULT NULL,
  DESC varchar(200) DEFAULT NULL,
  NAME varchar(20) DEFAULT NULL,
  REQUEST_CONTENT clob,
  RESPONSE_CONTENT clob,
  PRIMARY KEY (FLOW_ID,TRANS_ID)
);

-- ----------------------------
-- Records of cfg_flow_define
-- ----------------------------

-- ----------------------------
-- Table structure for cfg_flow_sequence
-- ----------------------------
DROP TABLE cfg_flow_sequence;
CREATE TABLE cfg_flow_sequence (
  ID varchar(20) NOT NULL,
  TRANS_ID int NOT NULL,
  SOURCE_REF varchar(8) DEFAULT NULL,
  TARGET_REF varchar(8) DEFAULT NULL,
  ENTRY_CONDITION varchar(128) DEFAULT NULL,
  DESC varchar(200) DEFAULT NULL,
  NAME varchar(20) DEFAULT NULL,
  SEQ_CODE varchar(20) DEFAULT NULL,
  PRIMARY KEY (ID,TRANS_ID)
);

-- ----------------------------
-- Records of cfg_flow_sequence
-- ----------------------------

-- ----------------------------
-- Table structure for cfg_trans_access
-- ----------------------------
DROP TABLE cfg_trans_access;
CREATE TABLE cfg_trans_access (
  ID int NOT NULL,
  TRANS_ID varchar(14) DEFAULT NULL,
  SYSTEM_ID varchar(10) DEFAULT NULL,
  ENABLE char(1) DEFAULT '1',
  PRIMARY KEY (ID)
);

-- ----------------------------
-- Records of cfg_trans_access
-- ----------------------------

-- ----------------------------
-- Table structure for cfg_trans_info
-- ----------------------------
DROP TABLE cfg_trans_info;
CREATE TABLE cfg_trans_info (
  ID int NOT NULL,
  TRANS_ID varchar(32) NOT NULL,
  TRANS_TYPE char(1) DEFAULT NULL,
  TRANS_NAME varchar(64) NOT NULL,
  TRANS_DESC varchar(256) DEFAULT NULL,
  ENABLE char(1) DEFAULT '1',
  CREATE_BY varchar(32) DEFAULT NULL,
  CREATE_DATE timestamp DEFAULT NULL,
  UPDATE_BY varchar(32) DEFAULT NULL,
  UPDATE_DATE timestamp DEFAULT NULL,
  INFO_ID varchar(32) DEFAULT NULL,
  SYSTEM_ID varchar(32) DEFAULT NULL,
  FLOW_INFO blob,
  DEMAND_ID varchar(20) DEFAULT NULL,
  PATH varchar(200) DEFAULT NULL,
  PRIMARY KEY (ID)
);

-- ----------------------------
-- Records of cfg_trans_info
-- ----------------------------

-- ----------------------------
-- Table structure for consul_envinfo
-- ----------------------------
DROP TABLE consul_envinfo;
CREATE TABLE consul_envinfo (
  id int NOT NULL,
  name varchar(20) DEFAULT NULL,
  path varchar(50) DEFAULT NULL,
  trans_id varchar(50) DEFAULT NULL,
  micro_id varchar(50) DEFAULT NULL,
  PRIMARY KEY (id)
);

-- ----------------------------
-- Records of consul_envinfo
-- ----------------------------

-- ----------------------------
-- Table structure for demand_info
-- ----------------------------
DROP TABLE demand_info;
CREATE TABLE demand_info (
  ID int NOT NULL,
  DEMAND_ID varchar(30) DEFAULT NULL,
  DEMAND_NAME varchar(200) DEFAULT NULL,
  PROCESSING_TIME timestamp DEFAULT NULL,
  ONLINE_TIME timestamp DEFAULT NULL,
  DEMAND_DESC varchar(500) DEFAULT NULL,
  ATTACHED_FILE varchar(500) DEFAULT NULL,
  STATUS varchar(1) DEFAULT NULL,
  CREATE_USER varchar(20) DEFAULT NULL,
  TRANS_ID varchar(20) DEFAULT NULL,
  PRIMARY KEY (ID)
);

-- ----------------------------
-- Records of demand_info
-- ----------------------------

-- ----------------------------
-- Table structure for environment_info_service
-- ----------------------------
DROP TABLE environment_info_service;
CREATE TABLE environment_info_service (
  id int NOT NULL,
  env_name varchar(20) DEFAULT NULL,
  env_desc varchar(200) DEFAULT NULL,
  ip varchar(20) DEFAULT NULL,
  port varchar(10) DEFAULT NULL,
  health varchar(100) DEFAULT NULL,
  status varchar(2) DEFAULT NULL,
  wsdl_path varchar(50) DEFAULT NULL,
  env_config_id int DEFAULT NULL,
  create_by varchar(20) DEFAULT NULL,
  create_date timestamp DEFAULT NULL,
  update_by varchar(20) DEFAULT NULL,
  update_date timestamp DEFAULT NULL,
  env_type char(1) DEFAULT NULL,
  PRIMARY KEY (id)
);

-- ----------------------------
-- Records of environment_info_service
-- ----------------------------

-- ----------------------------
-- Table structure for environment_info_trans
-- ----------------------------
DROP TABLE environment_info_trans;
CREATE TABLE environment_info_trans (
  id int NOT NULL,
  env_name varchar(20) DEFAULT NULL,
  env_desc varchar(200) DEFAULT NULL,
  ip varchar(20) DEFAULT NULL,
  port varchar(10) DEFAULT NULL,
  health varchar(100) DEFAULT NULL,
  status varchar(2) DEFAULT NULL,
  wsdl_path varchar(50) DEFAULT NULL,
  env_config_id int DEFAULT NULL,
  create_by varchar(20) DEFAULT NULL,
  create_date timestamp DEFAULT NULL,
  update_by varchar(20) DEFAULT NULL,
  update_date timestamp DEFAULT NULL,
  env_type char(1) DEFAULT NULL,
  PRIMARY KEY (id)
);

-- ----------------------------
-- Records of environment_info_trans
-- ----------------------------

-- ----------------------------
-- Table structure for env_config
-- ----------------------------
DROP TABLE env_config;
CREATE TABLE env_config (
  id int NOT NULL,
  conf_name varchar(20) DEFAULT NULL,
  conf_desc varchar(20) DEFAULT NULL,
  prototype varchar(20) DEFAULT NULL,
  status char(1) DEFAULT NULL,
  create_by varchar(20) DEFAULT NULL,
  create_date timestamp DEFAULT NULL,
  update_by varchar(20) DEFAULT NULL,
  update_date timestamp DEFAULT NULL,
  proto_id int DEFAULT NULL,
  content_type varchar(20) DEFAULT NULL,
  PRIMARY KEY (id)
);

-- ----------------------------
-- Records of env_config
-- ----------------------------

-- ----------------------------
-- Table structure for menu
-- ----------------------------
DROP TABLE menu;
CREATE TABLE menu (
  MENU_ID varchar(20) NOT NULL,
  MENU_TYPE varchar(2)  DEFAULT NULL,
  PATH varchar(250)  DEFAULT NULL,
  COMPONENT varchar(250)  DEFAULT NULL,
  REDIRECT varchar(250)  DEFAULT NULL,
  NAME varchar(250)  DEFAULT NULL,
  PARENTID varchar(20)  DEFAULT NULL,
  CREATE_USER varchar(30)  DEFAULT NULL,
  CREATE_TIME timestamp DEFAULT NULL,
  UPDATE_TIME timestamp DEFAULT NULL,
  STATUS varchar(2)  DEFAULT NULL,
  ICON varchar(100)  DEFAULT NULL,
  PRIMARY KEY (MENU_ID)
);

-- ----------------------------
-- Records of menu
-- ----------------------------
INSERT INTO menu VALUES ('24', '0', 'messageInfo/list', 'messageInfo/list', '', '报文编解码维护', '100063', 'admin', '2019-11-27 17:13:40', '2019-11-27 17:13:46', '1', 'process');
INSERT INTO menu VALUES ('62', '0', 'whiteList/list', 'whiteList/list', '', '黑名单管理', '100069', 'admin', '2019-11-13 14:43:17', '2019-11-25 16:53:10', '1', 'user');
INSERT INTO menu VALUES ('100005', '0', 'configCenter/list', 'configCenter/list', '', '配置中心', '100063', 'admin', '2019-11-13 08:42:01', '2019-11-13 11:01:06', '1', 'user');
INSERT INTO menu VALUES ('100006', '0', 'user/list', 'user/list', null, '用户管理', '100065', 'lierhong', '2019-11-12 09:01:51', '2019-11-12 16:11:51', '1', 'user');
INSERT INTO menu VALUES ('100007', '0', 'roles/list', 'roles/list', null, '角色管理', '100065', 'lierhong', '2019-11-12 09:01:51', '2019-11-12 16:47:55', '1', 'role');
INSERT INTO menu VALUES ('100008', '0', 'menu/list', 'menu/list', null, '菜单管理', '100065', 'lierhong', '2019-11-12 09:01:51', '2019-11-12 15:50:41', '1', 'menu');
INSERT INTO menu VALUES ('100021', '0', 'system/list', 'system/list', null, '系统信息', '100063', 'admin', '2019-11-12 09:01:51', '2019-11-13 08:40:23', '1', 'systemInfo');
INSERT INTO menu VALUES ('100031', '0', 'servicepub/list', 'servicepub/list', null, '服务发布', '100066', 'lvjianqiu', '2019-11-12 09:01:51', '2019-11-13 15:24:59', '1', 'serPub');
INSERT INTO menu VALUES ('100032', '0', 'registry/list', 'registry/list', null, '业务注册', '100066', 'admin', '2019-11-12 09:01:51', '2019-11-12 09:01:51', '1', 'serReg');
INSERT INTO menu VALUES ('100034', '0', 'protoInfo/list', 'protoInfo/list', null, '协议配置', '100063', 'admin', '2019-11-12 09:01:51', '2019-11-12 09:01:51', '1', 'protoinfo');
INSERT INTO menu VALUES ('100036', '0', 'logInfo/list', 'logInfo/list', null, '日志信息', '100068', 'lvjianqiu', '2019-11-12 09:01:51', '2019-11-12 09:01:51', '1', 'logInfo');
INSERT INTO menu VALUES ('100041', '0', 'serArran/list', 'serArran/list', null, '服务编排', '100067', 'lvjianqiu', '2019-11-12 09:01:51', '2019-11-12 09:01:51', '1', 'serArran');
INSERT INTO menu VALUES ('100063', '1', '/configMag', 'Layout', '/dashboard', '参数管理', null, 'admin', '2019-11-12 09:01:51', '2019-11-13 08:38:33', '1', 'process');
INSERT INTO menu VALUES ('100064', '1', '/basicInfoManage', 'Layout', '/dashboard', '环境管理', null, 'lierhong', '2019-11-12 09:01:51', '2019-11-12 09:01:51', '1', 'basicInfo');
INSERT INTO menu VALUES ('100065', '1', '/systemManage', 'Layout', '/dashboard', '系统管理', null, 'lierhong', '2019-11-12 09:01:51', '2019-11-12 09:01:51', '1', 'system');
INSERT INTO menu VALUES ('100066', '1', '/serviceManage', 'Layout', '/dashboard', '服务管理', null, 'lvjianqiu', '2019-11-12 09:01:51', '2019-11-12 09:01:51', '1', 'serviceManage');
INSERT INTO menu VALUES ('100067', '1', '/serviceArrangement', 'Layout', '/dashboard', '服务编排', null, 'lvjianqiu', '2019-11-12 09:01:51', '2019-11-12 09:01:51', '1', 'serArran');
INSERT INTO menu VALUES ('100068', '1', '/HisManage', 'Layout', '/dashboard', '历史查询', null, 'admin', '2019-11-12 09:01:51', '2019-11-13 08:38:33', '1', 'process');
INSERT INTO menu VALUES ('100069', '1', '/SecurityManage', 'Layout', '/dashboard', '安全管理', null, 'admin', '2019-11-12 09:01:51', '2019-11-13 08:38:33', '1', 'process');
INSERT INTO menu VALUES ('100070', '1', '/VersionManage', 'Layout', '/dashboard', '版本管理', null, 'admin', '2019-11-12 09:01:51', '2019-11-13 08:38:33', '1', 'process');
INSERT INTO menu VALUES ('100071', '0', 'releaBuild/list', 'releaBuild/list', '', '版本构建', '100070', 'admin', '2019-11-12 09:01:51', '2019-11-25 15:12:24', '1', 'process');
INSERT INTO menu VALUES ('100073', '0', '/PlatformEnvir/list', 'PlatformEnvir/list', '', '平台环境', '100064', 'admin', '2019-11-12 09:01:51', '2019-11-15 11:25:17', '1', 'process');
INSERT INTO menu VALUES ('100074', '0', '/businessEnvir/list', 'businessEnvir/list', '', '业务环境', '100064', 'admin', '2019-11-12 09:01:51', '2019-11-15 11:25:23', '1', 'process');
INSERT INTO menu VALUES ('100183', '0', 'MicEnMan/list', 'MicEnMan/list', '', '注册信息配置', '100066', 'admin', '2019-11-12 09:01:51', '2019-11-27 10:27:58', '0', 'MicEnMan');
INSERT INTO menu VALUES ('100185', '0', 'regCenter/list', 'regCenter/list', '', '注册中心', '100066', 'admin', '2019-11-14 08:29:05', null, '1', 'user');
INSERT INTO menu VALUES ('100186', '1', '/requirementManage', 'Layout', '/dashboard', '需求管理', '', 'admin', '2019-11-12 09:01:51', '2019-11-15 11:24:35', '1', 'process');
INSERT INTO menu VALUES ('100187', '0', 'requirementReg/list', 'requirementReg/list', '', '需求登记', '100186', 'admin', '2019-11-12 09:01:51', '2019-11-25 15:11:33', '1', 'process');
INSERT INTO menu VALUES ('100188', '0', 'protocolInfo/list', 'protocolInfo/list', '', '协议编解码维护', '100063', 'admin', '2019-11-27 18:03:20', null, '1', 'process');
INSERT INTO menu VALUES ('100189', '0', 'bufferMan/list', 'bufferMan/list', '', '缓存管理', '100063', 'admin', '2019-12-02 15:23:35', null, '1', 'process');

-- ----------------------------
-- Table structure for message_codec_info
-- ----------------------------
DROP TABLE message_codec_info;
CREATE TABLE message_codec_info (
  id int NOT NULL,
  codec_name varchar(100) DEFAULT NULL,
  codec_class varchar(100) DEFAULT NULL,
  codec_type varchar(10) DEFAULT NULL,
  message_type varchar(10) DEFAULT NULL,
  status varchar(10) DEFAULT NULL,
  codec_desc varchar(255) DEFAULT NULL,
  create_user varchar(50) DEFAULT NULL,
  create_time timestamp NULL DEFAULT NULL,
  update_user varchar(50) DEFAULT NULL,
  update_time timestamp NULL DEFAULT NULL,
  PRIMARY KEY (id)
);

-- ----------------------------
-- Records of message_codec_info
-- ----------------------------

-- ----------------------------
-- Table structure for micro_service_envinfo
-- ----------------------------
DROP TABLE micro_service_envinfo;
CREATE TABLE micro_service_envinfo (
  id int NOT NULL,
  env_name varchar(20) DEFAULT NULL,
  env_desc varchar(255) DEFAULT NULL,
  ip varchar(20) DEFAULT NULL,
  port varchar(10) DEFAULT NULL,
  path varchar(50) DEFAULT NULL,
  PRIMARY KEY (id)
);

-- ----------------------------
-- Records of micro_service_envinfo
-- ----------------------------

-- ----------------------------
-- Table structure for protocol_codec_info
-- ----------------------------
DROP TABLE protocol_codec_info;
CREATE TABLE protocol_codec_info (
  id int NOT NULL,
  codec_name varchar(100) DEFAULT NULL,
  codec_class varchar(100) DEFAULT NULL,
  codec_type varchar(10) DEFAULT NULL,
  protocol_id varchar(10) DEFAULT NULL,
  status varchar(10) DEFAULT NULL,
  codec_desc varchar(255) DEFAULT NULL,
  create_user varchar(50) DEFAULT NULL,
  create_time timestamp NULL DEFAULT NULL,
  update_user varchar(50) DEFAULT NULL,
  update_time timestamp NULL DEFAULT NULL,
  PRIMARY KEY (id)
);

-- ----------------------------
-- Records of protocol_codec_info
-- ----------------------------

-- ----------------------------
-- Table structure for protocol_config
-- ----------------------------
DROP TABLE protocol_config;
CREATE TABLE protocol_config (
  ID int NOT NULL,
  READ_TIMEOUT int DEFAULT NULL,
  TIMEOUT int DEFAULT NULL,
  IS_EBCDIC char(1) DEFAULT NULL,
  IS_DES char(1) DEFAULT NULL,
  REQ_ENCODING varchar(10) DEFAULT NULL,
  RES_ENCODING varchar(10) DEFAULT NULL,
  DATA_TYPE varchar(10) DEFAULT NULL,
  HEADER varchar(200) DEFAULT NULL,
  PRE_LENGTH int DEFAULT NULL,
  PRELEN_TYPE varchar(255) DEFAULT NULL,
  COMPLETION_TYPE varchar(255) DEFAULT NULL,
  ITSELF varchar(255) DEFAULT NULL,
  METHOD_TYPE varchar(10) DEFAULT NULL,
  REFLECT_CLASSNAME varchar(30) DEFAULT NULL,
  PRIMARY KEY (ID)
);

-- ----------------------------
-- Records of protocol_config
-- ----------------------------

-- ----------------------------
-- Table structure for role_info
-- ----------------------------
DROP TABLE role_info;
CREATE TABLE role_info (
  ROLE_ID int NOT NULL,
  ROLE_NAME varchar(50)  DEFAULT NULL,
  DESCRIBE varchar(250)  DEFAULT NULL,
  CREATE_USER varchar(20)  DEFAULT NULL,
  CREATE_TIME timestamp DEFAULT NULL,
  UPDATE_TIME timestamp DEFAULT NULL,
  STATUS varchar(2)  DEFAULT NULL,
  PRIMARY KEY (ROLE_ID)
);

-- ----------------------------
-- Records of role_info
-- ----------------------------
INSERT INTO role_info VALUES ('100007', 'admin', '管理员', null, '2019-11-12 09:01:51', '2019-11-13 08:46:21', '1');
INSERT INTO role_info VALUES ('100011', 'develop', 'ESB开发', 'lierhong', '2019-11-12 09:01:51', '2019-11-12 09:01:51', '1');
INSERT INTO role_info VALUES ('100013', 'outer', '外围系统', 'lierhong', '2019-11-12 09:01:51', '2019-11-12 09:01:51', '0');
INSERT INTO role_info VALUES ('100014', '测试001', '测试001', 'admin', '2019-11-12 09:01:51', '2019-11-12 16:11:55', '0');

-- ----------------------------
-- Table structure for role_menu
-- ----------------------------
DROP TABLE role_menu;
CREATE TABLE role_menu (
  ROLE_ID varchar(6)  NOT NULL,
  MENU_ID varchar(6)  NOT NULL,
  CREATE_USER varchar(30)  DEFAULT NULL,
  CREATE_TIME timestamp DEFAULT NULL,
  UPDATE_TIME timestamp DEFAULT NULL,
  STATUS varchar(2)  DEFAULT NULL,
  PRIMARY KEY (ROLE_ID,MENU_ID)
);

-- ----------------------------
-- Records of role_menu
-- ----------------------------
INSERT INTO role_menu VALUES ('100007', '100005', 'admin', '2019-12-03 10:43:24', null, null);
INSERT INTO role_menu VALUES ('100007', '100006', 'admin', '2019-12-03 10:43:24', null, null);
INSERT INTO role_menu VALUES ('100007', '100007', 'admin', '2019-12-03 10:43:24', null, null);
INSERT INTO role_menu VALUES ('100007', '100008', 'admin', '2019-12-03 10:43:24', null, null);
INSERT INTO role_menu VALUES ('100007', '100021', 'admin', '2019-12-03 10:43:24', null, null);
INSERT INTO role_menu VALUES ('100007', '100031', 'admin', '2019-12-03 10:43:24', null, null);
INSERT INTO role_menu VALUES ('100007', '100032', 'admin', '2019-12-03 10:43:24', null, null);
INSERT INTO role_menu VALUES ('100007', '100034', 'admin', '2019-12-03 10:43:24', null, null);
INSERT INTO role_menu VALUES ('100007', '100036', 'admin', '2019-12-03 10:43:24', null, null);
INSERT INTO role_menu VALUES ('100007', '100041', 'admin', '2019-12-03 10:43:24', null, null);
INSERT INTO role_menu VALUES ('100007', '100063', 'admin', '2019-12-03 10:43:24', null, null);
INSERT INTO role_menu VALUES ('100007', '100064', 'admin', '2019-12-03 10:43:24', null, null);
INSERT INTO role_menu VALUES ('100007', '100065', 'admin', '2019-12-03 10:43:24', null, null);
INSERT INTO role_menu VALUES ('100007', '100066', 'admin', '2019-12-03 10:43:24', null, null);
INSERT INTO role_menu VALUES ('100007', '100067', 'admin', '2019-12-03 10:43:24', null, null);
INSERT INTO role_menu VALUES ('100007', '100068', 'admin', '2019-12-03 10:43:24', null, null);
INSERT INTO role_menu VALUES ('100007', '100069', 'admin', '2019-12-03 10:43:24', null, null);
INSERT INTO role_menu VALUES ('100007', '100070', 'admin', '2019-12-03 10:43:24', null, null);
INSERT INTO role_menu VALUES ('100007', '100071', 'admin', '2019-12-03 10:43:24', null, null);
INSERT INTO role_menu VALUES ('100007', '100073', 'admin', '2019-12-03 10:43:24', null, null);
INSERT INTO role_menu VALUES ('100007', '100074', 'admin', '2019-12-03 10:43:24', null, null);
INSERT INTO role_menu VALUES ('100007', '100183', 'admin', '2019-12-03 10:43:24', null, null);
INSERT INTO role_menu VALUES ('100007', '100185', 'admin', '2019-12-03 10:43:24', null, null);
INSERT INTO role_menu VALUES ('100007', '100186', 'admin', '2019-12-03 10:43:24', null, null);
INSERT INTO role_menu VALUES ('100007', '100187', 'admin', '2019-12-03 10:43:24', null, null);
INSERT INTO role_menu VALUES ('100007', '100188', 'admin', '2019-12-03 10:43:24', null, null);
INSERT INTO role_menu VALUES ('100007', '100189', 'admin', '2019-12-03 10:43:24', null, null);
INSERT INTO role_menu VALUES ('100007', '24', 'admin', '2019-12-03 10:43:24', null, null);
INSERT INTO role_menu VALUES ('100007', '62', 'admin', '2019-12-03 10:43:24', null, null);

-- ----------------------------
-- Table structure for scp_service_log
-- ----------------------------
DROP TABLE scp_service_log;
CREATE TABLE scp_service_log (
  ID int NOT NULL,
  TRANS_LOG_ID varchar(32) DEFAULT NULL,
  SOURCE_SYSTEM varchar(30) DEFAULT NULL,
  TARGET_SYSTEM varchar(30) DEFAULT NULL,
  REQUEST_DATA varchar(4000) DEFAULT NULL,
  RESPONSE_DATA varchar(4000) DEFAULT NULL,
  SERVICE_ID varchar(30) DEFAULT NULL,
  IP varchar(30) DEFAULT NULL,
  PORT varchar(30) DEFAULT NULL,
  PATH varchar(50) DEFAULT NULL,
  REQUEST_DATE timestamp DEFAULT NULL,
  RESPONSE_DATE timestamp DEFAULT NULL,
  PLATFORM_TIME int DEFAULT NULL,
  HANDLE_TIME int DEFAULT NULL,
  STATUS char(1) DEFAULT NULL,
  CREATE_DATE timestamp DEFAULT NULL,
  NODE_ID varchar(30) DEFAULT NULL,
  ERROR_MSG varchar(500) DEFAULT NULL,
  FLOW_ID varchar(20) DEFAULT NULL,
  PRIMARY KEY (ID)
);

-- ----------------------------
-- Records of scp_service_log
-- ----------------------------

-- ----------------------------
-- Table structure for scp_trans_log
-- ----------------------------
DROP TABLE scp_trans_log;
CREATE TABLE scp_trans_log (
  ID int NOT NULL,
  MSG_ID varchar(32) DEFAULT NULL,
  SOURCE_SYSTEM varchar(30) DEFAULT NULL,
  TARGET_SYSTEM varchar(30) DEFAULT NULL,
  REQUEST_DATA varchar(4000) DEFAULT NULL,
  RESPONSE_DATA varchar(4000) DEFAULT NULL,
  TRANS_ID varchar(30) DEFAULT NULL,
  IP varchar(30) DEFAULT NULL,
  PORT varchar(30) DEFAULT NULL,
  PATH varchar(50) DEFAULT NULL,
  REQUEST_DATE timestamp DEFAULT NULL,
  RESPONSE_DATE timestamp DEFAULT NULL,
  PLATFORM_TIME int DEFAULT NULL,
  HANDLE_TIME int DEFAULT NULL,
  STATUS char(1) DEFAULT NULL,
  CREATE_DATE timestamp DEFAULT NULL,
  NODE_ID varchar(30) DEFAULT NULL,
  ERROR_MSG varchar(500) DEFAULT NULL,
  PRIMARY KEY (ID)
);

-- ----------------------------
-- Records of scp_trans_log
-- ----------------------------

-- ----------------------------
-- Table structure for service_define
-- ----------------------------
DROP TABLE service_define;
CREATE TABLE service_define (
  ID int NOT NULL,
  SERVICE_ID varchar(32) DEFAULT NULL,
  SERVICE_NAME varchar(64) DEFAULT NULL,
  SYSTEM_ID varchar(10) DEFAULT NULL,
  ENABLE char(1) DEFAULT NULL,
  SERVICE_DESC varchar(256) DEFAULT NULL,
  CREATE_BY varchar(32) DEFAULT NULL,
  CREATE_DATE timestamp DEFAULT NULL,
  UPDATE_BY varchar(32) DEFAULT NULL,
  UPDATE_DATE timestamp DEFAULT NULL,
  INFO_ID varchar(32) DEFAULT NULL,
  SERVICE_TYPE char(1) DEFAULT NULL,
  PATH varchar(200) DEFAULT NULL,
  PRIMARY KEY (ID)
);

-- ----------------------------
-- Records of service_define
-- ----------------------------

-- ----------------------------
-- Table structure for service_env_rel
-- ----------------------------
DROP TABLE service_env_rel;
CREATE TABLE service_env_rel (
  ID int NOT NULL,
  SERVICE_DEFINE_ID varchar(32) DEFAULT NULL,
  ENV_INFO_ID int DEFAULT NULL,
  PRIMARY KEY (ID)
);

-- ----------------------------
-- Records of service_env_rel
-- ----------------------------

-- ----------------------------
-- Table structure for service_exception
-- ----------------------------
DROP TABLE service_exception;
CREATE TABLE service_exception (
  ID varchar(8) NOT NULL,
  TRANS_ID int NOT NULL,
  FLOW_ID varchar(8) NOT NULL,
  TRY_TIMES int DEFAULT NULL,
  RESPONSE_DATA clob,
  WRONG_IGNORE char(1) DEFAULT NULL,
  ERRORDESC varchar(200) DEFAULT NULL,
  IS_TRY char(1) DEFAULT NULL,
  PRIMARY KEY (ID,TRANS_ID)
);

-- ----------------------------
-- Records of service_exception
-- ----------------------------

-- ----------------------------
-- Table structure for service_info
-- ----------------------------
DROP TABLE service_info;
CREATE TABLE service_info (
  ID int NOT NULL,
  REQUEST_DATA clob,
  RESPONSE_DATA clob,
  IS_SYNC char(1) DEFAULT NULL,
  CALLBACK_URL varchar(200) DEFAULT NULL,
  INTERFACE_TYPE char(1) DEFAULT NULL,
  INFO_ID varchar(32) DEFAULT NULL,
  REFLECT_CLASSNAME varchar(255) DEFAULT NULL,
  PRIMARY KEY (ID)
);

-- ----------------------------
-- Records of service_info
-- ----------------------------

-- ----------------------------
-- Table structure for stage_info
-- ----------------------------
DROP TABLE stage_info;
CREATE TABLE stage_info (
  ID int NOT NULL,
  PK_VALUE varchar(32) DEFAULT NULL,
  TARGET_KEY varchar(255) DEFAULT NULL,
  MANAGER_MODE char(1) DEFAULT NULL,
  FIX_VALUE varchar(255) DEFAULT NULL,
  STAGE_TYPE char(1) DEFAULT NULL,
  PRIMARY KEY (ID)
);

-- ----------------------------
-- Records of stage_info
-- ----------------------------

-- ----------------------------
-- Table structure for system_info
-- ----------------------------
DROP TABLE system_info;
CREATE TABLE system_info (
  system_id int NOT NULL,
  system_number varchar(20) DEFAULT NULL,
  system_abbreviation varchar(20) DEFAULT NULL,
  system_name varchar(100) DEFAULT NULL,
  system_desc varchar(200) DEFAULT NULL,
  create_user varchar(30) DEFAULT NULL,
  create_time timestamp NOT NULL,
  update_time timestamp NOT NULL,
  status varchar(2) DEFAULT NULL,
  PRIMARY KEY (system_id)
);

-- ----------------------------
-- Records of system_info
-- ----------------------------
INSERT INTO system_info VALUES ('100882', '110', 'ABS', '综合前端', '综合前端', 'admin', '2019-11-12 09:33:37', '2019-11-21 18:52:14', '1');
INSERT INTO system_info VALUES ('100883', '120', 'ATMP', 'ATM前置', 'ATM前置', 'admin', '2019-11-12 09:33:37', '2019-11-12 18:20:29', '1');
INSERT INTO system_info VALUES ('100884', '140', 'CNAPS2', '二代支付', '二代支付', 'admin', '2019-11-12 09:33:37', '2019-11-12 18:20:27', '1');
INSERT INTO system_info VALUES ('100885', '210', 'UCTFE', '贷记卡前置', '贷记卡前置', 'admin', '2019-11-12 09:33:37', '2019-11-12 18:20:30', '1');
INSERT INTO system_info VALUES ('100886', '213', 'CCAS', '信用卡审批系统', '信用卡审批系统', 'admin', '2019-11-12 09:33:37', '2019-11-12 18:20:33', '1');
INSERT INTO system_info VALUES ('100887', '280', 'ISS', '国际结算系统', '国际结算系统', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100888', '290', 'CCM', '信贷管理系统', '信贷管理系统', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100889', '450', 'PCM', '个贷业务系统', '个贷业务系统', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100890', '452', 'BBSP', '票据池', '票据池', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100891', '455', 'FMMP', '基金理财销售平台', '基金理财销售平台', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100892', '457', 'ENDAS', '电子国债', '电子国债', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100893', '461', 'ECDS', '电子商业汇票系统', '电子商业汇票系统', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100894', '471', 'CRM', '客户关系管理系统', '客户关系管理系统', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100895', '472', 'ECIF', '客户信息管理（ECIF）系统', '客户信息管理（ECIF）系统', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100896', '479', 'PMDS', '贵金属代销系统', '贵金属代销系统', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100897', '651', 'ESVS', '电子验印系统', '电子验印系统', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100898', '652', 'BBCA', '银企对账', '银企对账', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100899', '656', 'ZFJS', '支付结算平台', '支付结算平台', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100900', '657', 'MBP', '移动金融平台', '移动金融平台', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100901', '672', 'ITO', '智能厅堂', '智能厅堂', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100902', '673', 'PQE', '报价引擎', '报价引擎', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100903', '675', 'IRS', '内部评级系统', '内部评级系统', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100904', '676', 'CALLC', '信用卡客服系统', '信用卡客服系统', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100905', '677', 'ICMS', 'IC卡业务系统', 'IC卡业务系统', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100906', '678', 'EDP', '专家决策平台', '专家决策平台', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100907', '803', 'GCOP', '集中作业系统', '集中作业系统', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100908', '806', 'ESB', '企业服务总线', '企业服务总线', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100909', '810', 'SOP', '核心系统', '核心系统', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100910', '870', 'EBANK', '网银内管系统', '网银内管系统', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100911', '880', 'JADE', '外联平台', '外联平台', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100912', 'ICS', 'ICS', '身份核查', '身份核查', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100913', 'SOP', 'COP', '柜面服务系统（COP）', '柜面服务系统（COP）', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100914', 'BPEL', 'BPEL', 'BPEL', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100915', '8020', 'CCRP', '支付客户备付金存管系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100916', '8021', 'ATMIS', '关联交易系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100917', '8023', 'EHR', '人力资源管理系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100918', '8011', 'ITSM', '一体化服务管理平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100919', '8025', 'X-FUNDS', '代客外汇衍生交易系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100920', '8030', 'DZHD', '电子回单系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100921', '8032', 'CONT', '合同管理系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100922', '8040', 'WXSL', '微信营销平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100923', '8062', 'TYZF', '统一支付平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100924', '8061', 'PMP', '产品管理平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100925', '8063', 'SmartBank', '智慧银行', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100926', '8053', 'X-FUNDSFTA', '代客外汇衍生系统自贸区环境', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100927', '8064', 'ACS', 'ACS综合前置', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100928', '8066', 'XPad', '个人外汇系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100929', '8069', 'ECIFMSG', '消息推送平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100930', '8070', 'ZXGL', '直销管理系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100931', '8088', 'P2P', '资金托管', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100932', '8090', 'RMBKJZF', '人民币跨境支付系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100933', '8050', 'JSBAUDIT', '非现场审计系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100934', '8089', 'SSFQZ', '实时反欺诈系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100935', '8093', 'FHOA', '分行OA', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100936', '8100', 'RCT', '互联网风险信息采集分析系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100937', '8028', 'HLWXS', '互联网销售平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100938', '8123', 'TYJZ', '统一价值', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100939', '8128', 'tivoli', '系统管理tivoli监控系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100940', '8136', 'CCYZF', '串串赢支付系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100941', '8138', 'MDYW', '端末设备运维与管理系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100942', '8142', 'DKCT', '代客外汇货币掉期（传统区）', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100943', '8143', 'DKZM', '代客外汇货币掉期（自贸区）', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100944', '8145', 'CSHXT', '车生活系统', '车生活系统', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100945', '8147', 'WLPT', '网联平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100946', '8002', 'ODC', '外部数据采集平台', '外部数据采集平台', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100947', '467', 'IBPS', '网银互联平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100948', '468', 'VAS', '代客资产系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100949', '463', 'OPICS', '资金风险管理系统', '请求->6010端口', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100950', '8001', 'MDM', '移动设备管理系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100951', '8014', 'LMS', '本外币头寸管理系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100952', '8012', 'BPEL', '组合服务平台', 'ESB业务编排平台', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100953', '8015', 'TYYW', '同业业务管理系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100954', '8016', 'GYL', '供应链系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100955', '8017', 'ZJSP', '资金交易在线审批系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100956', '658', 'HPM', '贷款定价系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100957', '8018', 'JFY', '综合积分系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100958', '8022', 'CMSP', '现金管理系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100959', '8027', 'PMS', '参数管理系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100960', '8034', 'ZXKF', '在线客服', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100961', '8043', 'WDGL', '网贷管理平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100962', '8045', 'FACECALC', '人脸识别计算单元', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100963', '8065', 'IFTSII', '第三方交易资金存管系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100964', '459', 'CGS', '财管系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100965', '8068', 'ZNJK', '智能金库与配送管理系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100966', '8067', 'xqd', '社区帮', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100967', '8073', 'CMS', '风险缓释系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100968', '473', 'EFSS', '资金监管（大宗商品）', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100969', '8074', 'FUND', '基金直连平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100970', '8019', 'YDSP', '移动视频系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100971', '8084', 'HCE', '银联云端支付平台', '银联云端支付平台', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100972', '8099', 'ATMV', 'ATMV', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100973', '8109', 'KHDC', '客户调查报告', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100974', '8117', 'TYWL', '同业网络平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100975', '8118', 'YXPT', '616项目营销平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100976', '8113', 'RWA', 'RWA与资本管理', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100977', '8119', 'CJXT', '616项目抽奖系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100978', '8120', 'payGateway', '网银支付', '网银支付', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100979', '123456', 'ZHPOC', 'ZHPOC', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100980', '8051', 'TYBS', '统一报送平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100981', '8115', 'YDYL', '移动医疗平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100983', '8153', 'ZHYQ', '智慧引擎', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100984', '8157', 'BWPT', '报文平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100985', '8159', 'ZZZL', '中债智联', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100986', '8163', 'BBYX', '报表类影像自动录入系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100987', '8177', 'HXWX', '徐州蕙享无限项目', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100988', '8189', 'SPKF', '视频客服', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100989', '8194', 'NLP', '自然语言NLP平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100990', '8196', 'I9', 'I9减值估值系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100991', '8198', 'SUMMIT', '新资金风险管理系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100992', '211', 'TLQZ', '通联前置', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100993', '8218', 'CSHZF', '城商行支付系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100994', '8224', 'RBA', 'RBA工商流程机器人', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100995', '8223', 'JCJ', '积存金交易系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100996', '8003', 'VTM', 'VTM', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100997', '8004', 'CREWS', '对公客户风险预警系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100998', '8005', 'WFP', '流程服务平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('100999', '8010', 'EMAILP', '电子邮件平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101000', '458', 'SMSP', '短信平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101001', 'WCP', 'WCP', '公众服务平台（微信、易信、支付宝）', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101002', '8888', 'TEST', 'TEST', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101003', '8013', 'WCP', '公众服务平台（微信、易信、支付宝）', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101004', '222', 'IFTS', '第三方存管', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101005', '8036', 'ZCTG', '保险与股权资产托管系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101006', '8024', 'XWGQ', '资金监管(小微股权)', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101007', '8035', 'WMS', '财富管理', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101008', '659', 'QGZP', '全国支票影像', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101009', '8046', 'DKHS', '贷款核算平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101010', '8047', 'KJHS', '会计核算平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101011', '475', 'ODS', '数据平台ODS', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101012', '8058', 'NETCOOL', '网络监控系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101013', '8060', 'ZJGL', '主机系统管理', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101014', '8059', 'GRC', '内控合规和操作风险管理系统 ', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101015', '8071', 'ZXIQ', '资信信息查询系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101016', '8072', 'TYDA', '统一数据展现平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101017', '8075', 'MARC', '营销工作平台(前端)', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101018', '8076', 'MARS', '营销工作平台(后端)', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101019', '8079', 'INETNETPORTAL', '外网门户系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101020', '8083', 'ZCZJH', '资产证券化', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101021', '8081', 'NCA', '非信贷资产减值系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101022', '8140', 'EWMGL', '二维码管理系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101023', '8176', 'GTZQ', '柜台债券', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101024', '8175', 'PADOA', '移动OA', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101025', '8174', 'YDPD', '移动工作平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101026', '8217', 'YCGT', '远程柜台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101027', '8220', 'FNC', '理财代销系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101028', '8006', 'DIRECTBANK', '直销银行', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101029', '8007', 'EPAY', '支付聚合平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101030', '214', 'CCCS', '信用卡催收系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101031', '453', 'BAFE', '银保通', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101032', 'BPEL01', 'BPEL', '组合服务平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101033', '462', 'SSTS', '自助终端', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101034', '8029', 'KMPRO', '知识管理系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101035', '8031', 'ZHXXFB', '综合信息发布系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101036', '8039', 'CES', '硬币兑换联网系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101037', '130', 'POS', 'POS', 'POSP', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101038', '8041', 'PORTAL', '信用卡门户', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101039', '8042', 'BRV', '录音录像系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101040', '8044', 'Robot', '智能语义分析系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101041', '8037', 'CGGL', '采购管理系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101042', '8085', 'QYYX', '企业邮箱', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101043', '8097', 'SJYFW', '数据云服务管理平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101044', '8098', 'RCZKMH', '融创智库门户', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101045', '8095', 'YXDX', '营销短信外包', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101046', '8102', 'ZCTGYWGL', '资产托管业务管理系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101047', '8103', 'pwdMP', '密码管理平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101048', '470', 'MPBANK', '手机银行', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101049', '8110', 'LMP', '额度管理平台', '额度管理平台', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101050', '8107', 'YYJK', '应用监控平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101051', '8131', 'ZCTGQZ', '资产托管业务管理系统前置', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101052', '8134', 'DZYZ', '电子印章项目', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101053', '8135', 'YCFW', '银承防伪系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101054', '8137', 'ZNJJR', '智能机器人', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101055', '8127', 'XCSJ', '现场审计系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101056', '8139', 'JNWBZF', '境内外币支付', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101057', '8054', 'NBDZ', '内部对账系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101058', '8146', 'NCRM', '零售CRM', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101059', '430', 'WOPPlatform', 'WOP平台', 'WOP平台', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101060', '8165', 'ZJSB', '证件识别平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101061', '8162', 'QYWX', '企业微信', '1', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101062', '8155', 'CBSQ', '核心交易查询系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101063', '000000', 'TEST2', 'TEST', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101064', '8170', 'WDHS', '分期核算系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101065', '8181', 'XDZHD', '新电子回单系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101066', '8188', 'PORTAL', '信用卡门户', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101067', '8187', 'LCZR', '理财份额转让平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101068', '8192', 'JFGL', '缴费综合管理平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101069', '8193', 'EDSNEW', '新专家决策平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101070', '8197', 'QXY', '青信云平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101071', '8204', 'TLHX', '通联信用卡', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101072', '8124', 'XQSPT', '新清算平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101073', '8214', 'XQSPT', '新清算平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101074', '8201', 'BXFKJ', '便携发卡机', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101075', '8008', 'YDSD', '移动收单', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101076', '8009', 'ESociety', '融e社区', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101077', '8026', 'CALLD', '借记卡电话银行', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101078', '8082', 'OA', 'OA系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101079', '8091', 'CIP', '自助发卡机', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101080', '8078', 'TAX', '税务管理系统 ', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101081', '8094', 'CFCASign', '电子签章系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101083', '8116', 'SOSJXKH', '616绩效考核', '616系统616绩效考核', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101084', '8111', 'TYCK', '统一查控', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101085', '8122', 'JSPAS', '绩效考核', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101086', '8096', 'GAPSFZJH', '外联平台负载均衡', '外联平台负载均衡环境', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101087', '8125', '616JSH', '616积生活', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101088', '8130', 'CPS', '统一调度平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101089', '8132', 'ZNTG', '智能投顾', '智能投顾', 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101090', '7777', 'F5', 'F5', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101091', '9999', 'F5', 'F5', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101092', '8151', 'QKL', '税e融区块链', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101093', '8152', 'ZCMD', '制裁名单', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101094', '8057', 'SYJZ', '苏银金租', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101095', '8178', 'DFGL', '党费管理平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101096', '8171', 'YYJQR', '语意机器人', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101097', '8182', 'PHJR', '普惠金融平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101098', '8183', 'YYSB', '语音识别平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101099', '8184', 'ZHGL', '单位账户管理系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101100', '8185', 'YYHC', '语音合成平台', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101101', '8186', 'ZNWH', '智能外呼系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101102', '8195', 'PZSB', '智能凭证识别系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101103', '10000', '10000', '10000', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101104', '8203', 'BEbank', '企业手机银行', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101105', '8209', 'ZCBQ', '资产保全系统', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('101106', '8227', 'RLCAPP', '融联创APP', null, 'admin', '2019-11-12 09:33:37', '2019-11-12 09:33:37', '1');
INSERT INTO system_info VALUES ('222222', '8888', 'SCP', '服务组合平台', '1111', 'admin', '2019-12-02 10:31:17', '2019-12-02 15:10:52', '1');

-- ----------------------------
-- Table structure for trans_content
-- ----------------------------
DROP TABLE trans_content;
CREATE TABLE trans_content (
  ID int NOT NULL,
  TRANS_ID int DEFAULT NULL,
  REQUEST_CONTENT clob,
  RESPONSE_CONTENT clob,
  PRIMARY KEY (ID)
);

-- ----------------------------
-- Records of trans_content
-- ----------------------------

-- ----------------------------
-- Table structure for trans_define_info
-- ----------------------------
DROP TABLE trans_define_info;
CREATE TABLE trans_define_info (
  ID int NOT NULL,
  REQUEST_DATA clob,
  RESPONSE_DATA clob,
  IS_SYNC char(1) DEFAULT NULL,
  CALLBACK_URL varchar(200) DEFAULT NULL,
  INTERFACE_TYPE char(1) DEFAULT NULL,
  INFO_ID varchar(32) DEFAULT NULL,
  PRIMARY KEY (ID)
);

-- ----------------------------
-- Records of trans_define_info
-- ----------------------------

-- ----------------------------
-- Table structure for trans_env_rel
-- ----------------------------
DROP TABLE trans_env_rel;
CREATE TABLE trans_env_rel (
  ID int NOT NULL,
  TRANS_INFO_ID int DEFAULT NULL,
  ENV_INFO_ID int DEFAULT NULL,
  PRIMARY KEY (ID)
);

-- ----------------------------
-- Records of trans_env_rel
-- ----------------------------

-- ----------------------------
-- Table structure for user_info
-- ----------------------------
DROP TABLE user_info;
CREATE TABLE user_info (
  ID varchar(20) NOT NULL,
  USER_NAME varchar(20)  DEFAULT NULL,
  NAME varchar(20)  DEFAULT NULL,
  PASSWORD varchar(50)  DEFAULT NULL,
  PUB_SYSTEM varchar(20)  DEFAULT NULL,
  CREATE_USER varchar(30)  DEFAULT NULL,
  CREATE_TIME timestamp DEFAULT NULL,
  UPDATE_TIME timestamp DEFAULT NULL,
  STATUS varchar(2)  DEFAULT NULL,
  PRIMARY KEY (ID)
);

-- ----------------------------
-- Records of user_info
-- ----------------------------
INSERT INTO user_info VALUES ('100116', 'admin', '超级管理员', 'e10adc3949ba59abbe56e057f20f883e', null, null, '2019-11-12 09:01:51', '2019-11-12 16:14:59', '1');
INSERT INTO user_info VALUES ('100174', 'sunchao', '孙超', '96e79218965eb72c92a549dd5a330112', '100908', 'admin', '2019-11-12 09:01:51', '2019-11-29 09:46:31', '1');
INSERT INTO user_info VALUES ('100175', 'outer', 'OUTER', '96e79218965eb72c92a549dd5a330112', '100951', 'admin', '2019-11-12 09:01:51', '2019-11-28 15:23:03', '1');
INSERT INTO user_info VALUES ('100215', 'testq', 'testq', '670b14728ad9902aecba32e22fa4f6bd', '100888', 'admin', '2019-11-12 09:01:51', '2019-11-12 09:01:51', '1');
INSERT INTO user_info VALUES ('100216', 'test', 'test001', '96e79218965eb72c92a549dd5a330112', '100885', 'admin', '2019-11-12 09:01:51', '2019-11-28 13:24:40', '1');
INSERT INTO user_info VALUES ('100254', 'LiSi', '??', '670b14728ad9902aecba32e22fa4f6bd', '100883', 'admin', '2019-11-12 09:01:51', '2019-11-12 09:01:51', '1');
INSERT INTO user_info VALUES ('100275', '测试001', '用户', '670b14728ad9902aecba32e22fa4f6bd', '100887', 'admin', '2019-11-12 09:01:51', '2019-11-12 09:01:51', '1');
INSERT INTO user_info VALUES ('100277', 'Charon', 'Charon', '670b14728ad9902aecba32e22fa4f6bd', '100891', 'admin', '2019-11-29 09:55:23', null, '1');

-- ----------------------------
-- Table structure for user_role
-- ----------------------------
DROP TABLE user_role;
CREATE TABLE user_role (
  ID varchar(20)  NOT NULL,
  USER_ID varchar(20)  DEFAULT NULL,
  ROLE_ID varchar(20)  DEFAULT NULL,
  CREATE_USER varchar(30)  DEFAULT NULL,
  CREATE_TIME timestamp DEFAULT NULL,
  UPDATE_TIME timestamp DEFAULT NULL,
  STATUS varchar(20)  DEFAULT NULL,
  PRIMARY KEY (ID)
);

-- ----------------------------
-- Records of user_role
-- ----------------------------
INSERT INTO user_role VALUES ('100019', '100117', '100012', null, '2019-11-12 09:01:51', '2019-11-12 09:01:51', null);
INSERT INTO user_role VALUES ('100040', '100114', '100013', null, '2019-11-12 09:01:51', '2019-11-12 09:01:51', null);
INSERT INTO user_role VALUES ('100041', '100114', '100011', null, '2019-11-12 09:01:51', '2019-11-12 09:01:51', null);
INSERT INTO user_role VALUES ('100060', '100134', '100013', null, '2019-11-12 09:01:51', '2019-11-12 09:01:51', null);
INSERT INTO user_role VALUES ('100084', '100154', '100011', null, '2019-11-12 09:01:51', '2019-11-12 09:01:51', null);
INSERT INTO user_role VALUES ('100085', '100157', '100013', null, '2019-11-12 09:01:51', '2019-11-12 09:01:51', null);
INSERT INTO user_role VALUES ('100100', '100116', '100007', null, '2019-11-12 09:01:51', '2019-11-12 09:01:51', null);
INSERT INTO user_role VALUES ('100101', '100174', '100011', null, '2019-11-12 09:01:51', '2019-11-12 09:01:51', null);
INSERT INTO user_role VALUES ('100102', '100175', '100013', null, '2019-11-12 09:01:51', '2019-11-12 09:01:51', null);
INSERT INTO user_role VALUES ('100103', '100176', '100013', null, '2019-11-12 09:01:51', '2019-11-12 09:01:51', null);