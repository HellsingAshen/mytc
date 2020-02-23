package com.git.utils;

import java.sql.Connection;

import javax.sql.DataSource;
import java.sql.SQLException;

public class ConnectionUtils {
    /* 和线程绑定的 connection */
    private ThreadLocal<Connection> tl = new ThreadLocal<Connection>();

    public void setDataSource(DataSource dataSource) {
        this.dataSource = dataSource;
    }

    private DataSource dataSource;

    public Connection getThreadConnection(){
        Connection conn = tl.get();
        try {
            if (conn == null) {
                conn = dataSource.getConnection();
                tl.set(conn);
            }
            return conn;
        } catch (Exception e){
            throw new RuntimeException(e);
        }
    }

    // remove connection from thread
    public  void removeThreadConnection(){
        tl.remove();
    }
}
