
    def close(self):
        self.selectors.unregister(self.socket)
        self.socket.close()