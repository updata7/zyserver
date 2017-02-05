DROP TABLE IF EXISTS `tb_account`;
CREATE TABLE `tb_account` (
	`platform_id` smallint(8) unsigned DEFAULT '0' COMMENT '平台id',
	`user_id` bigint(20) NOT NULL AUTO_INCREMENT COMMENT '用户id',
	`loginname` varchar(24) NOT NULL COMMENT '登录账号',
	`password` varchar(24) NOT NULL COMMENT '密码',
	`user_status` smallint(8) DEFAULT '0' COMMENT '玩家在线状态',
	`create_data` datetime NOT NULL COMMENT '创建时间，这里指注册账号的时间',
	`last_modified_date` datetime NOT NULL,
	PRIMARY KEY (`user_id`),
	KEY `index_pid` (`platform_id`) USING BTREE,
	KEY `index_uid` (`user_id`) USING BTREE,
	KEY `index_loginname` (`loginname`) USING BTREE
)ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='玩家账号表';

DROP TABLE IF EXISTS `tb_player`;
CREATE TABLE `tb_player` (
	`player_id` smallint(8) unsigned NOT NULL COMMENT '玩家id',
	`nick_name` varchar(24) DEFAULT '' COMMENT '玩家昵称',
	`level` bigint(20) DEFAULT '0' COMMENT '玩家等级',
	`gold` bigint(20) DEFAULT '0' COMMENT '金币',
	PRIMARY KEY (`player_id`)
)ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='玩家表';

DROP TABLE IF EXISTS `tb_task`;
CREATE TABLE `tb_task` (
	`player_id` bigint(20) NOT NULL COMMENT '玩家id',
	`task_id` bigint(20) NOT NULL COMMENT '任务id',
	`task_status` smallint(8) NOT NULL COMMENT '任务状态',
	`task_progress` smallint(8) NOT NULL COMMENT '任务进度',
	PRIMARY KEY (`player_id`)
)ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='任务表';