# -*- mode: ruby -*-
# vi: set ft=ruby :

VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  config.vm.box = "ubuntu/trusty64"
  config.vm.network :private_network, type: "dhcp"

  config.vm.provider :virtualbox do |v|
    v.customize ["modifyvm", :id, "--memory", 4096]
    v.customize ["modifyvm", :id, "--cpus", 2]
  end

  config.vm.synced_folder "./", "/home/vagrant", id: "vagrant-root",nfs:true

  config.vm.provision :shell do |sh|
    sh.path = "scripts/vagrant_provision.sh"
  end
end