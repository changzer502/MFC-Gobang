/*
 Navicat Premium Data Transfer

 Source Server         : MySQL
 Source Server Type    : MySQL
 Source Server Version : 80025
 Source Host           : localhost:3306
 Source Schema         : gobang

 Target Server Type    : MySQL
 Target Server Version : 80025
 File Encoding         : 65001

 Date: 28/12/2021 09:51:08
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for g_result
-- ----------------------------
DROP TABLE IF EXISTS `g_result`;
CREATE TABLE `g_result`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `result` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `userId` int NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `userId`(`userId`) USING BTREE,
  CONSTRAINT `g_result_ibfk_1` FOREIGN KEY (`userId`) REFERENCES `g_user` (`id`) ON DELETE SET NULL ON UPDATE CASCADE
) ENGINE = InnoDB AUTO_INCREMENT = 29 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of g_result
-- ----------------------------
INSERT INTO `g_result` VALUES (1, '黑棋胜利', 1);
INSERT INTO `g_result` VALUES (2, '黑棋胜利', 1);
INSERT INTO `g_result` VALUES (3, '黑棋胜利', 1);
INSERT INTO `g_result` VALUES (4, '黑棋胜利', 1);
INSERT INTO `g_result` VALUES (5, '白棋胜利', 1);
INSERT INTO `g_result` VALUES (6, '黑棋胜利', 1);
INSERT INTO `g_result` VALUES (7, '黑棋胜利', 1);
INSERT INTO `g_result` VALUES (8, '黑棋胜利', 1);
INSERT INTO `g_result` VALUES (9, '黑棋胜利', 1);
INSERT INTO `g_result` VALUES (10, '白棋胜利', 1);
INSERT INTO `g_result` VALUES (11, '白棋胜利', 1);
INSERT INTO `g_result` VALUES (12, '黑棋胜利', 1);
INSERT INTO `g_result` VALUES (13, '白棋胜利', 2);
INSERT INTO `g_result` VALUES (14, '黑棋胜利', 1);
INSERT INTO `g_result` VALUES (15, '白棋胜利', 1);
INSERT INTO `g_result` VALUES (16, '黑棋胜利', 1);
INSERT INTO `g_result` VALUES (17, '白棋胜利', 1);
INSERT INTO `g_result` VALUES (18, '白棋胜利', 2);
INSERT INTO `g_result` VALUES (19, '黑棋胜利', 1);
INSERT INTO `g_result` VALUES (20, '黑棋胜利', 1);
INSERT INTO `g_result` VALUES (21, '黑棋胜利', 2);
INSERT INTO `g_result` VALUES (22, '白棋胜利', 2);
INSERT INTO `g_result` VALUES (23, '白棋胜利', 2);
INSERT INTO `g_result` VALUES (24, '黑棋胜利', 2);
INSERT INTO `g_result` VALUES (25, '黑棋胜利', NULL);
INSERT INTO `g_result` VALUES (26, '黑棋胜利', NULL);
INSERT INTO `g_result` VALUES (27, '白棋胜利', NULL);
INSERT INTO `g_result` VALUES (28, '黑棋胜利', NULL);
INSERT INTO `g_result` VALUES (29, '黑棋胜利', NULL);

-- ----------------------------
-- Table structure for g_user
-- ----------------------------
DROP TABLE IF EXISTS `g_user`;
CREATE TABLE `g_user`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `userName` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `id`(`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 8 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of g_user
-- ----------------------------
INSERT INTO `g_user` VALUES (1, 'admin');
INSERT INTO `g_user` VALUES (2, '游客');

SET FOREIGN_KEY_CHECKS = 1;
