CREATE USER IF NOT EXISTS 'plexLike'@'localhost' IDENTIFIED BY 'plexLike';

CREATE DATABASE IF NOT EXISTS plexLike;

USE plexLike;

GRANT ALL PRIVILEGES ON plexLike.* TO 'plexLike'@'localhost';
