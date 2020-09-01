-- --------------------------------------------------------
-- 호스트:                          127.0.0.1
-- 서버 버전:                        10.4.8-MariaDB - mariadb.org binary distribution
-- 서버 OS:                        Win64
-- HeidiSQL 버전:                  10.2.0.5599
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


-- musicapp 데이터베이스 구조 내보내기
CREATE DATABASE IF NOT EXISTS `musicapp` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `musicapp`;

-- 테이블 musicapp.buy_music 구조 내보내기
CREATE TABLE IF NOT EXISTS `buy_music` (
  `REGISTER_NUM` int(11) NOT NULL,
  `USER_NUM` int(11) NOT NULL,
  PRIMARY KEY (`REGISTER_NUM`,`USER_NUM`),
  KEY `buy_music_ibfk_2` (`USER_NUM`),
  CONSTRAINT `buy_music_ibfk_1` FOREIGN KEY (`REGISTER_NUM`) REFERENCES `music` (`REGISTER_NUM`) ON DELETE CASCADE,
  CONSTRAINT `buy_music_ibfk_2` FOREIGN KEY (`USER_NUM`) REFERENCES `user_` (`USER_NUM`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 테이블 데이터 musicapp.buy_music:~0 rows (대략적) 내보내기
/*!40000 ALTER TABLE `buy_music` DISABLE KEYS */;
/*!40000 ALTER TABLE `buy_music` ENABLE KEYS */;

-- 테이블 musicapp.chart 구조 내보내기
CREATE TABLE IF NOT EXISTS `chart` (
  `CHART_NAME` char(10) NOT NULL,
  `MUSIC_CNT` int(11) NOT NULL,
  PRIMARY KEY (`CHART_NAME`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 테이블 데이터 musicapp.chart:~0 rows (대략적) 내보내기
/*!40000 ALTER TABLE `chart` DISABLE KEYS */;
INSERT INTO `chart` (`CHART_NAME`, `MUSIC_CNT`) VALUES
	('TopChart', 0);
/*!40000 ALTER TABLE `chart` ENABLE KEYS */;

-- 테이블 musicapp.manager 구조 내보내기
CREATE TABLE IF NOT EXISTS `manager` (
  `NAME_` char(7) NOT NULL,
  `RRN` char(15) NOT NULL,
  `SEX` char(1) NOT NULL,
  `BDATE` char(20) NOT NULL,
  `MANAGER_NUM` int(11) NOT NULL,
  PRIMARY KEY (`MANAGER_NUM`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 테이블 데이터 musicapp.manager:~5 rows (대략적) 내보내기
/*!40000 ALTER TABLE `manager` DISABLE KEYS */;
INSERT INTO `manager` (`NAME_`, `RRN`, `SEX`, `BDATE`, `MANAGER_NUM`) VALUES
	('lee', '980101-2434244', 'f', '1998-01-01', 1),
	('park', '980505-1235244', 'm', '1998-05-05', 2),
	('choi', '930303-2112442', 'f', '1993-03-03', 3),
	('lee', '950225-1256342', 'm', '1995-02-25', 4),
	('shin', '981203-1783213', 'm', '1998-12-03', 5);
/*!40000 ALTER TABLE `manager` ENABLE KEYS */;

-- 테이블 musicapp.music 구조 내보내기
CREATE TABLE IF NOT EXISTS `music` (
  `GENRE` char(10) NOT NULL,
  `ALBUM` varchar(30) NOT NULL,
  `RELEASE_DATE` char(20) NOT NULL,
  `LYRICIST` char(20) NOT NULL,
  `COMPOSER` char(20) NOT NULL,
  `TITLE` varchar(30) NOT NULL,
  `ARTIST` varchar(20) NOT NULL,
  `CHARTSCORE` int(11) NOT NULL,
  `PRICE` int(11) NOT NULL,
  `REGISTER_NUM` int(11) NOT NULL,
  `MANAGER_NUM` int(11) NOT NULL,
  `CHART_NAME` char(10) NOT NULL,
  PRIMARY KEY (`REGISTER_NUM`),
  KEY `MANAGER_NUM` (`MANAGER_NUM`),
  KEY `CHART_NAME` (`CHART_NAME`),
  CONSTRAINT `music_ibfk_1` FOREIGN KEY (`MANAGER_NUM`) REFERENCES `manager` (`MANAGER_NUM`),
  CONSTRAINT `music_ibfk_2` FOREIGN KEY (`CHART_NAME`) REFERENCES `chart` (`CHART_NAME`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 테이블 데이터 musicapp.music:~6 rows (대략적) 내보내기
/*!40000 ALTER TABLE `music` DISABLE KEYS */;
INSERT INTO `music` (`GENRE`, `ALBUM`, `RELEASE_DATE`, `LYRICIST`, `COMPOSER`, `TITLE`, `ARTIST`, `CHARTSCORE`, `PRICE`, `REGISTER_NUM`, `MANAGER_NUM`, `CHART_NAME`) VALUES
	('ballade', 'new', '2013-03-24', 'aa', 'bb', 'this is first song', 'cc', 0, 1000, 1, 1, 'TopChart'),
	('dance', 'book', '2017-06-12', 'dd', 'ee', 'this is second song', 'ff', 0, 1000, 2, 2, 'TopChart'),
	('classic', 'bob', '2015-01-22', 'gg', 'hh', 'this is third song', 'ii', 0, 1000, 3, 3, 'TopChart'),
	('agitation', 'coffee', '2019-12-01', 'jj', 'kk', 'this is fourth song', 'll', 0, 1000, 4, 4, 'TopChart'),
	('etc', 'cake', '2016-02-09', 'mm', 'nn', 'this is fifth song', 'oo', 0, 1000, 5, 5, 'TopChart'),
	('dance', 'note', '2018-08-15', 'pp', 'qq', 'this is sixth song', 'rr', 0, 1000, 6, 2, 'TopChart'),
	('etc', 'eyes', '2014-04-27', 'ss', 'tt', 'this is seventh song', 'uu', 0, 1000, 7, 5, 'TopChart'),
	('ballade', 'val', '2017-02-24', 'vv', 'ww', 'this is eighth song', 'xx', 0, 1000, 8, 1, 'TopChart');
/*!40000 ALTER TABLE `music` ENABLE KEYS */;

-- 테이블 musicapp.playlist 구조 내보내기
CREATE TABLE IF NOT EXISTS `playlist` (
  `USER_NUM` int(11) NOT NULL,
  `PLAYLIST_NUM` int(11) NOT NULL,
  PRIMARY KEY (`USER_NUM`,`PLAYLIST_NUM`),
  CONSTRAINT `FK_playlist_user_` FOREIGN KEY (`USER_NUM`) REFERENCES `user_` (`USER_NUM`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 테이블 데이터 musicapp.playlist:~6 rows (대략적) 내보내기
/*!40000 ALTER TABLE `playlist` DISABLE KEYS */;
INSERT INTO `playlist` (`USER_NUM`, `PLAYLIST_NUM`) VALUES
	(1, 1),
	(2, 2),
	(3, 3),
	(4, 4),
	(5, 5),
	(6, 6);
/*!40000 ALTER TABLE `playlist` ENABLE KEYS */;

-- 테이블 musicapp.reg_in_pla 구조 내보내기
CREATE TABLE IF NOT EXISTS `reg_in_pla` (
  `REGISTER_NUM` int(11) NOT NULL,
  `USER_NUM` int(11) NOT NULL,
  `PLAYLIST_NUM` int(11) NOT NULL,
  PRIMARY KEY (`REGISTER_NUM`,`PLAYLIST_NUM`),
  KEY `FK_reg_in_pla_user_` (`USER_NUM`,`PLAYLIST_NUM`),
  CONSTRAINT `FK_reg_in_pla_music` FOREIGN KEY (`REGISTER_NUM`) REFERENCES `music` (`REGISTER_NUM`) ON DELETE CASCADE,
  CONSTRAINT `FK_reg_in_pla_user_` FOREIGN KEY (`USER_NUM`, `PLAYLIST_NUM`) REFERENCES `playlist` (`USER_NUM`, `PLAYLIST_NUM`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 테이블 데이터 musicapp.reg_in_pla:~0 rows (대략적) 내보내기
/*!40000 ALTER TABLE `reg_in_pla` DISABLE KEYS */;
/*!40000 ALTER TABLE `reg_in_pla` ENABLE KEYS */;

-- 테이블 musicapp.user_ 구조 내보내기
CREATE TABLE IF NOT EXISTS `user_` (
  `NAME_` char(7) NOT NULL,
  `SEX` char(1) NOT NULL,
  `BDATE` char(20) NOT NULL,
  `ADDRESS` varchar(30) DEFAULT NULL,
  `EMAIL` char(30) NOT NULL,
  `ID` varchar(30) NOT NULL,
  `PASSWORD_` varchar(30) NOT NULL,
  `USER_NUM` int(11) NOT NULL,
  `COIN` int(11) NOT NULL,
  `MANAGER_NUM` int(11) NOT NULL,
  PRIMARY KEY (`USER_NUM`),
  KEY `MANAGER_NUM` (`MANAGER_NUM`),
  CONSTRAINT `user__ibfk_1` FOREIGN KEY (`MANAGER_NUM`) REFERENCES `manager` (`MANAGER_NUM`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 테이블 데이터 musicapp.user_:~0 rows (대략적) 내보내기
/*!40000 ALTER TABLE `user_` DISABLE KEYS */;
INSERT INTO `user_` (`NAME_`, `SEX`, `BDATE`, `ADDRESS`, `EMAIL`, `ID`, `PASSWORD_`, `USER_NUM`, `COIN`, `MANAGER_NUM`) VALUES
	('park', 'f', '1999-04-30', 'Ulsan', 'park@naver.com', 'park', '1234', 1, 0, 1),
	('kim', 'm', '1998-02-14', 'Busan', 'kim@gmail.com', 'kim', '1234', 2, 0, 2),
	('choi', 'f', '2001-07-03', 'Seoul', 'choi@naver.com', 'choi', '1234', 3, 0, 3),
	('kang', 'm', '1993-09-26', 'Daejeon', 'kang@naver.com', 'kang', '1234', 4, 0, 4),
	('lee', 'm', '1998-11-01', 'Gangneung', 'lee@gmail.com', 'lee', '1234', 5, 0, 5),
	('han', 'f', '1995-08-23', 'Yeosu', 'han@gmail.com', 'han', '1234', 6, 0, 1);
/*!40000 ALTER TABLE `user_` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
