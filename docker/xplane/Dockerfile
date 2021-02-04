ARG BASEIMAGE=ubuntu:18.04
FROM ${BASEIMAGE}
USER root

ENV DEBIAN_FRONTEND=noninteractive

# Installing xplane prerequisites and launch script
COPY scripts/install/install_xplane_prerequisites.sh /tmp/install.sh
COPY third_party/xplane/launch.sh /opt/xplane/launch.sh
RUN /tmp/install.sh

# Add non-root user
RUN useradd --create-home --shell /bin/bash uxplane

# Preparing xplane configuration folder
ARG USER=uxplane
RUN mkdir /home/${USER}/.x-plane
RUN chown ${USER} /home/${USER}/.x-plane

# Non-root default user
USER ${USER}

CMD ["/bin/bash", "/opt/xplane/launch.sh"]
