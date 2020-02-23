package com.git.utils;

import java.sql.SQLException;

public class TransactionManager {

    ConnectionUtils connectionUtils;

    public void setConnectionUtils(ConnectionUtils connectionUtils) {
        this.connectionUtils = connectionUtils;
    }

    public void beginTransaction(){
        try {
            System.out.println("==== Begin " + connectionUtils.getThreadConnection() + "\n");
            connectionUtils.getThreadConnection().setAutoCommit(false);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void commit(){
        try {
            System.out.println("==== Commit " + connectionUtils.getThreadConnection() + "\n");
            connectionUtils.getThreadConnection().commit();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void rollback(){
        try {
            System.out.println("==== Rollback " + connectionUtils.getThreadConnection() + "\n");
            connectionUtils.getThreadConnection().rollback();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void release(){
        try {
            System.out.println("==== Release " + connectionUtils.getThreadConnection() + "\n");

            connectionUtils.getThreadConnection().close();
            connectionUtils.removeThreadConnection();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
