.PHONY: xplane
xplane: ../dc-extends-xplane.yml
	@mkdir -p ${HOME}/.x-plane-docker
	@$(MAKE) -C ../.. build
	@$(MAKE) -C ../.. build-xplane
